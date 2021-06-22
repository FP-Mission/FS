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

#define DEBUG_PRINT(x,...) Fw::Logger::logMsg(x,##__VA_ARGS__);
//#define DEBUG_PRINT(x,...)

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
    // Default ping key value
    this->pingKey = 0;
    this->rbCommandInCtn = 0;
    this->rbCommandOutCtn = 0;
    this->textDataReceived = false;
    this->SBDIX.mtQueued = 0;
    this->lastMailboxCheck = getTime();
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
    if(MAILBOX_INTERVAL != 0) {
        Fw::Time currentTime = getTime();
        this->mailboxCheckMutex.lock();
        Fw::Time delta = Fw::Time::sub(currentTime, this->lastMailboxCheck);
        this->mailboxCheckMutex.unLock();
        if(delta.getSeconds() > MAILBOX_INTERVAL) {
            this->addCommand("AT+SBDIX");
        }
    }
}

void RockBlockComponentImpl:: configureHardware() {
    this->sendRockBlockCommand("AT"); // Send first command to receive OK response
    this->addCommand("AT+SBDMTA?");
    this->addCommand("AT+CSQ");
    // Mailbox check at launch if enabled
    if(MAILBOX_INTERVAL != 0) {
        this->addCommand("AT+SBDIX");
    }
}

void RockBlockComponentImpl:: addCommand(std::string command) {
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
            DEBUG_PRINT("Add RockBlock command %s\n", reinterpret_cast<POINTER_CAST>(command.c_str()));
        }
    }
    this->rbCommandMutex.unLock();
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
        DEBUG_PRINT("RockBlock is not free, delay command %s\n", reinterpret_cast<POINTER_CAST>(command.c_str()));
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
    this->sendRockBlockCommand("AT", false);
    this->pingKey = key;
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
            this->log_ACTIVITY_LO_RckBlck_CSQ(signalQuality);
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

            // Save last time the mailbox have been checked
            this->mailboxCheckMutex.lock();
            this->lastMailboxCheck = getTime();
            this->mailboxCheckMutex.unLock();

            res = sscanf(pointer + 8, "%u, %u, %u, %u, %u, %u", 
                                        &SBDIX.moStatus, &SBDIX.moMsn,
                                        &SBDIX.mtStatus, &SBDIX.mtMsn,
                                        &SBDIX.mtLength, &SBDIX.mtQueued);

            if(res == 6) {
                DEBUG_PRINT("[RockBlock] moStatus: %u, moMsN: %u, mtStatus: %u, mtMsn: %u, mtLength: %u, mtQueued: %u\n", 
                                SBDIX.moStatus, SBDIX.moMsn, SBDIX.mtStatus, SBDIX.mtMsn, SBDIX.mtLength, SBDIX.mtQueued);

                if(SBDIX.moStatus >= 0 && SBDIX.moStatus <= 2) {
                    Fw::Logger::logMsg("[RockBlock] Message, if any, transferred successfully (%u)\n", SBDIX.moMsn);
                } else {
                    this->log_WARNING_LO_RckBlck_UnableToSend(SBDIX.moStatus);
                }

                switch (SBDIX.mtStatus) {
                    case 0:
                        // No SBD message to receive from the GSS
                        break;
                    case 1:
                        // SBD message successfully received from the GSS.
                        this->log_ACTIVITY_HI_RckBlck_MessageReceived(SBDIX.mtMsn, SBDIX.mtQueued);
                        // depends on requested data : SBDRB for binary and SBDRT for text
                        this->addCommand("AT+SBDRB");
                        break;
                    case 2:
                        this->log_WARNING_HI_RckBlck_MailboxCheckFail();
                        break;
                }
            } else {
                Fw::Logger::logMsg("[ERROR] Unable to parse SBDIX RockBlock response, res=%u\n", res);
            }
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
            }

            // If messages are queued, get them
            if(SBDIX.mtQueued > 0) {
                this->addCommand("AT+SBDIX");
            }

        } else if(detectCommand("+SBDRT:", pointer)) {
            this->textDataReceived = true;
            // Data received are received on next line and will be processed below
            DEBUG_PRINT("[RockBlock] +SBDRT:\n");
        } else if (detectCommand("SBDRING", pointer)) {
            this->log_ACTIVITY_HI_RckBlck_RingAlert();
            this->addCommand("AT+SBDIXA");
        } else if(detectCommand("\r\n", pointer) && buffsize == 2) {
            // Empty line
            //DEBUG_PRINT("[RockBlock] Emtpy\n", pointer);
        } else {
            if(this->textDataReceived) {
                Fw::Logger::logMsg("[RockBlock] %s\n", reinterpret_cast<POINTER_CAST>(pointer));
                // If messages are queued, get them
                if(SBDIX.mtQueued > 0) {
                    this->addCommand("AT+SBDIX");
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
