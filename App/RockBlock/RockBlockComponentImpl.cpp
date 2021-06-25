// ======================================================================
// \title  RockBlockComponentImpl.cpp
// \author jonathan
// \brief  cpp file for RockBlock component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <App/RockBlock/RockBlockComponentImpl.hpp>

#include "Fw/Logger/Logger.hpp"
#include "Fw/Types/BasicTypes.hpp"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG_PRINT(x,...) Fw::Logger::logMsg(x,##__VA_ARGS__);
#define DEBUG_PRINT(x,...)

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

RockBlockComponentImpl ::RockBlockComponentImpl(const char *const compName) 
    : RockBlockComponentBase(compName) {
        this->fpCommandBuffer.setData(this->fpCommandData);
        this->fpCommandBuffer.setSize(FP_COMMAND_BUFFER_SIZE);
}

void RockBlockComponentImpl ::init(const NATIVE_INT_TYPE queueDepth,
                                   const NATIVE_INT_TYPE instance) {
    RockBlockComponentBase::init(queueDepth, instance);
    this->simulatorMode = false;
    // RockBlock is considered as available at launch
    this->rockBlockIsOk = true;
    this->csqInterval = CSQ_INTERVAL_LOW;
    // Default ping key value
    this->pingKey = 0;
    this->pingCtn = 0;
    this->rbCommandInCtn = 0;
    this->rbCommandOutCtn = 0;
    this->textDataReceived = false;
    this->SBDIX.mtQueued = 0;
    this->ringAlertsCtn = 0;
    this->noNetworkCtn = 0;
    this->lastMailboxCheck = getTime();
    this->mailboxCheckOnGoing = false;
}

// Step 0: The linux serial driver keeps its storage externally. This means that
// we need to supply it some buffers to
//        work with. This code will loop through our member variables holding
//        the buffers and send them to the linux serial driver.  'preamble' is
//        automatically called after the system is constructed, before the
//        system runs at steady-state. This allows for initialization code that
//        invokes working ports.
void RockBlockComponentImpl::preamble(void) {
    for (NATIVE_INT_TYPE buffer = 0; buffer < DR_MAX_NUM_BUFFERS; buffer++) {
        // Assign the raw data to the buffer. Make sure to include the side of
        // the region assigned.
        this->m_serialRecvBuffers[buffer].setData(this->m_serialRecvData[buffer]);
        this->m_serialRecvBuffers[buffer].setSize(UART_READ_BUFF_SIZE);
        // Invoke the port to send the buffer out.
        this->serialBufferOut_out(0, this->m_serialRecvBuffers[buffer]);
    }
}

RockBlockComponentImpl ::~RockBlockComponentImpl(void) {}

void RockBlockComponentImpl::Run_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // Periodically send next command
    // When a command responds ("OK" or "ERROR"), the next pending command in the rbCommandBuffer
    // is automatically sent
    // However, if a command has been added to the queue and no command is supposed to respond soon,
    // the run scheduler empty the queue
    this->sendNextCommand();
    
    // Check when was the last mailbox check
    // Avoid concurrency issues
    this->mailboxCheckMutex.lock();
    bool checkMailbox_temp = this->mailboxCheckOnGoing;
    U8 ringAlertsCtn_temp = this->ringAlertsCtn;
    Fw::Time lastMailboxCheck_temp = this->lastMailboxCheck;
    this->mailboxCheckMutex.unLock();

    if(checkMailbox_temp == false) {
        if(MAILBOX_INTERVAL != 0) {
            Fw::Time currentTime = getTime();
            Fw::Time delta = Fw::Time::sub(currentTime, lastMailboxCheck_temp);
            // Periodically check mailbox if no check was performed until a long time
            if(delta.getSeconds() > MAILBOX_INTERVAL) {
                if(this->checkMailbox()) {
                    Fw::Logger::logMsg("[RockBlock] Periodic mailbox check\n");
                }
            // Check mailbox if messages have been received throuhg ringAlert but not correctly read 
            } else if(ringAlertsCtn_temp > 0) {
                if(this->checkMailbox()) {
                    Fw::Logger::logMsg("[RockBlock] Ring alert mailbox check\n");
                }
            }
        }
    }
}

void RockBlockComponentImpl:: configureHardware() {
    this->sendRockBlockCommand("AT"); // Send first command to receive OK response
    this->addCommand("AT+SBDMTA=1");
    this->addCommand("AT+SBDMTA?");
    this->addCommand("AT+CSQ");
    // Mailbox check at launch if enabled
    if(MAILBOX_INTERVAL != 0) {
        this->checkMailbox();
    }
}

bool RockBlockComponentImpl:: checkMailbox() {
    bool ret = false;
    this->mailboxCheckMutex.lock();
    // Check that mailbox check is not already on going
    if(this->mailboxCheckOnGoing == false) {
        if(this->addCommand("AT+SBDIX")) {
            // Update if command has been successfully added
            this->mailboxCheckOnGoing = true;
            ret = true;
        }
    }
    this->mailboxCheckMutex.unLock();
    return ret;
}

bool RockBlockComponentImpl:: addCommand(std::string command) {
    bool ret = false;
    this->rbCommandMutex.lock();
    U8 commandLength = command.size();
    if(commandLength > ROCKBLOCK_COMMAND_SIZE) {
        Fw::Logger::logMsg("[ERROR] RockBlock too long command: %d\n",
                           commandLength);
    } else {
        U8 newCtn = (this->rbCommandInCtn + 1) % ROCKBLOCK_COMMAND_BUFFER_SIZE;
        if(newCtn == this->rbCommandOutCtn) {
            Fw::Logger::logMsg("[ERROR] RockBlock sending queue full\n");
        } else {
            sprintf(&rbCommandBuffer[this->rbCommandInCtn][0], command.c_str(), commandLength);
            this->rbCommandInCtn = newCtn;
            ret = true;
            DEBUG_PRINT("Add RockBlock command %s\n", reinterpret_cast<POINTER_CAST>(command.c_str()));
        }
    }
    this->rbCommandMutex.unLock();
    return ret;
}

void RockBlockComponentImpl:: sendNextCommand() {
    this->rbCommandMutex.lock();
    // Send command if a new one has been stored
    if(this->rbCommandInCtn != this->rbCommandOutCtn) {

        // When command sent is AT+SBDRB, the module will directly responds with 
        // the binary data in the following frame :
        // AT+SBDRB\r<2 bytes length><x bytes data><2 bytes checksum>\r\n
        // We need to pass the driver in binary mode to avoid returning on end character (\n)
        // instead of at the end of the binary data
        if(detectCommand("AT+SBDRB", &rbCommandBuffer[this->rbCommandOutCtn][0])) {
            DEBUG_PRINT("Send SBDRB to receive %u bytes\n", SBDIX.mtLength);
            // 15 bytes overhead, see frame above:
            this->binaryMode_out(0, SBDIX.mtLength + 15);
        }

        std::string cmd(&rbCommandBuffer[this->rbCommandOutCtn][0]);
        // Increment out counter if command has been sent
        if(this->sendRockBlockCommand(cmd)) {
            this->rbCommandOutCtn = (this->rbCommandOutCtn + 1) % ROCKBLOCK_COMMAND_BUFFER_SIZE;
        } else {
            Fw::Logger::logMsg("[RockBlock] Command delayed %u/%u\n", this->rbCommandInCtn, this->rbCommandOutCtn);
        }
    } else {
        // DEBUG_PRINT("No pending command\n");
    }
    this->rbCommandMutex.unLock();
}

bool RockBlockComponentImpl:: sendRockBlockCommand(std::string command) {
    return this->sendRockBlockCommand(command, true);
}

bool RockBlockComponentImpl:: sendRockBlockCommand(std::string command, bool log) {
    serialMutex.lock();
    bool sent = false;
    if(this->rockBlockIsOk) {
        this->rockBlockIsOk = false;    // @todo Check concurrency, mutex ?
        char commandToSend[30]; 
        Fw::Buffer buffer;
        U16 size;

        if (this->simulatorMode) {
            size = command.size() + 2;
            sprintf(commandToSend, "~%s\r", command.c_str());
        } else {
            size = command.size() + 1;
            sprintf(commandToSend, "%s\r", command.c_str());
        }

        buffer.setData((U8*)commandToSend);
        buffer.setSize(size);
        this->serialSend_out(0, buffer);

        if(log) {
            Fw::LogStringArg arg(commandToSend);
            this->log_DIAGNOSTIC_RckBlck_CommandSent(arg);
        }
        sent = true;
    } else {
        Fw::Logger::logMsg("[WARNING] RockBlock is not free for command %s\n", reinterpret_cast<POINTER_CAST>(command.c_str()));
    }
    serialMutex.unLock();
    return sent;
}

bool RockBlockComponentImpl ::detectCommand(const char* command, const char* line) {
    bool found = true;
    for (int i = 0; i < strlen(command); i++) {
        found &= (command[i] == line[i]);
    }
    return found;
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void RockBlockComponentImpl ::PingIn_handler(const NATIVE_INT_TYPE portNum,
                                             U32 key) {
    // Save ping key to allow response in serialRecv_handler
    pingMutex.lock();
    // Try to directly send an AT command
    // If RockBlock is busy, next OK received will respond to the ping request
    this->csqIntervalMutex.lock();
    if(this->pingCtn == this->csqInterval - 1) {
        this->sendRockBlockCommand("AT+CSQ", false);
    } else {
        this->sendRockBlockCommand("AT", false);
    }
    this->csqIntervalMutex.unLock();
    this->pingKey = key;
    this->pingCtn = (this->pingCtn + 1) % this->csqInterval ;
    pingMutex.unLock();
}

void RockBlockComponentImpl ::RckBlck_SendCommand_cmdHandler(
    const FwOpcodeType opCode,
    const U32 cmdSeq,
    const Fw::CmdStringArg& AT_Command,
    const U8 mode
) {
    if(mode == 0) { // directly send command
        if(this->sendRockBlockCommand(AT_Command.toChar())) {
            this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
        } else {
            this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_EXECUTION_ERROR);
        }
    } else if (mode == 1) { // add command to command buffer
        this->addCommand(AT_Command.toChar());
        this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
    } else {
        this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_VALIDATION_ERROR);
    }
}

void RockBlockComponentImpl ::serialRecv_handler(
    const NATIVE_INT_TYPE portNum, Fw::Buffer &serBuffer,
    Drv::SerialReadStatus &status) {
    // We MUST return the buffer or the serial driver won't be able to reuse
    // it. The same buffer send call is used as we did in "preamble".  Since
    // the buffer's size was overwritten to hold the actual data size, we
    // need to reset it to the full data block size before returning it.

    // Grab the size (used amount of the buffer) and a pointer to the data in
    // the buffer
    U32 buffsize = static_cast<U32>(serBuffer.getSize());
    char *pointer = reinterpret_cast<char *>(serBuffer.getData());

    // Check for invalid read status, log an error, return buffer and abort if
    // there is a problem
    if (status != Drv::SER_OK) {
        Fw::Logger::logMsg("[WARNING] RockBlock serial received error: %d\n",
                           status);

        serBuffer.setSize(UART_READ_BUFF_SIZE);
        this->serialBufferOut_out(0, serBuffer);
        return;
    }
    // Make sure end of char is '\0'
    *(pointer + buffsize) = '\0';

    try {
        if(detectCommand("OK", pointer)) {
            this->rockBlockIsOk = true;

            // Ping response sent each time ping request was received
            // and RockBlock responds OK
            pingMutex.lock();
            if(this->pingKey != 0) {
                // OK is a response from the ping request
                // Do not overload logs
                PingOut_out(0, this->pingKey);
                this->pingKey = 0;
            } else {
                Fw::LogStringArg arg("OK");
                this->log_DIAGNOSTIC_RckBlck_Response(arg);
            }
            pingMutex.unLock();

            // Send next command when last command ack received
            this->sendNextCommand();
        } else if(detectCommand("ERROR", pointer)) {
            Fw::LogStringArg arg("ERROR");
            this->log_DIAGNOSTIC_RckBlck_Response(arg);
            this->rockBlockIsOk = true; // ok here means "free to receive commands"
            // Send next command when last command ack received
            this->sendNextCommand();
        } else if(detectCommand("+CSQ:", pointer)) {
            U8 signalQuality = atoi(pointer + 5);
            log_ACTIVITY_LO_RckBlck_CSQ(signalQuality);
            tlmWrite_RckBlck_RSSI(signalQuality);
            this->csqIntervalMutex.lock();
            if (signalQuality == 0) {
                this->csqInterval = CSQ_INTERVAL_LOW;
                // Count no network time
                if(this->noNetworkCtn <= 5) {
                    this->noNetworkCtn ++;
                }
            } else {
                this->csqInterval = CSQ_INTERVAL_HIGH;
                if(this->noNetworkCtn == 5) {
                    Fw::Logger::logMsg("[RockBlock] Network is back on, check mailbox\n");
                    this->checkMailbox();
                    this->noNetworkCtn = 0;
                }

            }
            this->csqIntervalMutex.unLock();
        }  else if(detectCommand("+SBDMTA:", pointer)) {
            Fw::LogStringArg arg(pointer);
            this->log_DIAGNOSTIC_RckBlck_Response(arg);
            // @todo Replace by custom event ?
            /*/
            U8 ringAllertEnabled = atoi(pointer + 8);
            if(ringAllertEnabled) {
                DEBUG_PRINT("[RockBlock] Ring alert enabled\n");
            } else {
                DEBUG_PRINT("[RockBlock] Ring alert disabled\n");
            }
            //*/
        } else if(detectCommand("+SBDIX:", pointer)) {            
            U8 res = 0;

            U16 mtQueued_temp;

            res = sscanf(pointer + 8, "%u, %u, %u, %u, %u, %u", 
                                        &SBDIX.moStatus, &SBDIX.moMsn,
                                        &SBDIX.mtStatus, &SBDIX.mtMsn,
                                        &SBDIX.mtLength, &mtQueued_temp);

            if(res == 6) {
                Fw::Logger::logMsg("[RockBlock] moStatus: %u, moMsN: %u, mtStatus: %u, mtMsn: %u, mtLength: %u, mtQueued: %u\n", SBDIX.moStatus, SBDIX.moMsn, SBDIX.mtStatus, SBDIX.mtMsn, SBDIX.mtLength, mtQueued_temp);

                if(SBDIX.moStatus >= 0 && SBDIX.moStatus <= 2) {
                    Fw::Logger::logMsg("[RockBlock] Message, if any, transferred successfully (%u)\n", SBDIX.moMsn);
                } else {
                    //this->log_WARNING_LO_RckBlck_UnableToSend(SBDIX.moStatus);
                }

                switch (SBDIX.mtStatus) {
                    case 0:
                        // No SBD message to receive from the GSS
                        SBDIX.mtQueued = mtQueued_temp;
                        this->log_ACTIVITY_HI_RckBlck_NoMessageReceived(SBDIX.mtMsn);
                        break;
                    case 1:
                        SBDIX.mtQueued = mtQueued_temp;
                        // SBD message successfully received from the GSS.
                        this->log_ACTIVITY_HI_RckBlck_MessageReceived(SBDIX.mtMsn, SBDIX.mtQueued);
                        this->mailboxCheckMutex.lock();
                        if(this->ringAlertsCtn >= 1) {
                            this->ringAlertsCtn--;
                        }
                        this->mailboxCheckMutex.unLock();
                        // depends on requested data : SBDRB for binary and SBDRT for text
                        this->addCommand("AT+SBDRB");
                        break;
                    case 2:
                        this->log_WARNING_HI_RckBlck_MailboxCheckFail();
                        break;
                }

                this->mailboxCheckMutex.lock();
                if(SBDIX.mtStatus <= 1) {
                    // Save last time the mailbox have been successfully checked
                    this->lastMailboxCheck = getTime();
                }
                this->mailboxCheckMutex.unLock();
            } else {
                Fw::Logger::logMsg("[ERROR] Unable to parse SBDIX RockBlock response, res=%u\n", res);
            }

            // Indicate that mailbox attempt is done
            this->mailboxCheckMutex.lock();
            this->mailboxCheckOnGoing = false;
            this->mailboxCheckMutex.unLock();

        } else if(detectCommand("AT+SBDRB", pointer)) {
            DEBUG_PRINT("[RockBlock] AT+SBDRB: %u \n", buffsize);

            // The SBD message is transferred formatted as follows:
            // {2-byte message length} + {binary SBD message} + {2-byte checksum}
            // Frame response : AT+SBDRB\r<2 bytes length><x bytes data><2 bytes checksum>\r\n
            char *framePointer = pointer + 9;
            U16 dataSize = (*framePointer << 8) + *(framePointer+1);
            // Data size indicated in received frame corresponds to buffer size returned (15 bytes overhead)
            if(dataSize == buffsize - 15) {
                DEBUG_PRINT("Binary message received: 0x%04X\n", dataSize);

                /*/ Print frame
                DEBUG_PRINT("Message:\n", buffsize - 15);  // 15 bytes overhead
                for(int i = 0; i < dataSize; i++) {
                    printf("%.2X", *(framePointer + 2 + i));
                }
                printf("\n");
                //*/

                // @todo Check checksum ?
                U16 checksum = (*(pointer + 2 + dataSize) << 8) + *(pointer + 3 + dataSize);
                DEBUG_PRINT("Checksum: %4X\n", checksum);

                if(dataSize <= FP_COMMAND_BUFFER_SIZE) {
                    FW_ASSERT(this->fpCommandBuffer.getData());
                    // Copy from data start (after 2 bytes length)
                    memcpy(this->fpCommandBuffer.getData(), framePointer + 2, dataSize);
                    this->fpCommandBuffer.setSize(dataSize);

                    if(this->isConnected_recvData_OutputPort(0)) {
                        this->recvData_out(0, this->fpCommandBuffer);
                    } else {
                        Fw::Logger::logMsg("[WARNING] RockBlock component is not connected for uplink\n");
                    }
                } else {
                    Fw::Logger::logMsg("[ERROR] Received RockBlock command is too big\n");
                }
            } else {
                Fw::Logger::logMsg("[ERROR] Unable to read binary message\n");
            }

            // If messages are queued, get them
            this->mailboxCheckMutex.lock();
            U8 ringAltertsCtn_temp = this->ringAlertsCtn;
            this->mailboxCheckMutex.unLock();
            // If ringAlterCtn > 0, checkMailbox will occur in Run_handler
            // Only check mailbox if messages are queued and ring alterts were not received
            if(SBDIX.mtQueued > 0 && ringAltertsCtn_temp == 0) {
                Fw::Logger::logMsg("[RockBlock] Binary messages pending in queue, check mailbox\n");
                this->checkMailbox();
            }

        } else if(detectCommand("+SBDRT:", pointer)) {
            this->textDataReceived = true;
            // Data received are received on next line and will be processed below
            DEBUG_PRINT("[RockBlock] +SBDRT:\n");
        } else if (detectCommand("SBDRING", pointer)) {
            this->log_ACTIVITY_HI_RckBlck_RingAlert();
            if(this->addCommand("AT+SBDIXA")) {
                this->mailboxCheckMutex.lock();
                this->mailboxCheckOnGoing = true;
                this->ringAlertsCtn++;
                this->mailboxCheckMutex.unLock();
            }
        } else if(detectCommand("\r\n", pointer) && buffsize == 2) {
            // Empty line
            //DEBUG_PRINT("[RockBlock] Emtpy\n", pointer);
        } else {
            if(this->textDataReceived) {
                Fw::Logger::logMsg("[RockBlock] %s\n", reinterpret_cast<POINTER_CAST>(pointer));
                // If messages are queued, get them
                if(SBDIX.mtQueued > 0) {
                    Fw::Logger::logMsg("[RockBlock] Text messages pending in queue, check mailbox\n");
                    this->checkMailbox();
                }
            } else {
                if(buffsize == 5 && detectCommand("AT", pointer)) {
                    // do not print "AT" echo, sent by ping request
                } else {
                    Fw::LogStringArg arg(pointer);
                    this->log_DIAGNOSTIC_RckBlck_Response(arg);
                }
            }
        }
    } catch (...) {
        Fw::Logger::logMsg("[ERROR] Unable to decode frame received from RockBlock\n");
    }

    // Return buffer (see above note)
    serBuffer.setSize(UART_READ_BUFF_SIZE);
    this->serialBufferOut_out(0, serBuffer);
}

U8 RockBlockComponentImpl::HexToByte(char hex) { 
    if (hex>='0' && hex<='9') {
        return hex - '0';
    } else if (hex>='A' && hex<='F') {
        return hex + 10 - 'A';
    } else if (hex>='a' && hex<='f') {
        return hex + 10 - 'a';
    }
    return 0;
}

}  // end namespace App
