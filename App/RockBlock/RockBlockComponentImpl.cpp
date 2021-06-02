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

#define DEBUG_PRINT(x, ...)  printf(x, ##__VA_ARGS__); fflush(stdout)
//#define DEBUG_PRINT(x,...)

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

RockBlockComponentImpl ::RockBlockComponentImpl(const char *const compName) 
    : RockBlockComponentBase(compName) {
        this->m_commandBuffer.setData(this->m_commandData);
        this->m_commandBuffer.setSize(COMMAND_BUFFER_SIZE);
}

void RockBlockComponentImpl ::init(const NATIVE_INT_TYPE queueDepth,
                                   const NATIVE_INT_TYPE instance) {
    RockBlockComponentBase::init(queueDepth, instance);
}

// Step 0: The linux serial driver keeps its storage externally. This means that
// we need to supply it some buffers to
//        work with. This code will loop through our member variables holding
//        the buffers and send them to the linux serial driver.  'preamble' is
//        automatically called after the system is constructed, before the
//        system runs at steady-state. This allows for initialization code that
//        invokes working ports.
void RockBlockComponentImpl::preamble(void) {
    this->commandInCtn = 0;
    this->commandOutCtn = 0;
    this->dataReceived = false;
    // RockBlock is considered as available at launch
    this->rockBlockIsOk = true;
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
    // When a command responds ("OK" or "ERROR"), the next pending command in the CommandBuffer
    // is automatically sent
    // However, if a command has been added to the queue and no command is supposed to respond soon,
    // the run scheduler empty the queue
    this->sendNextCommand();
}

void RockBlockComponentImpl:: configureHardware() {
    this->sendRockBlockCommand("AT"); // Send first command to receive OK response
    this->addCommand("AT+SBDMTA?");
    this->addCommand("AT+CSQ");
    //this->addCommand("AT+SBDIX");
}

void RockBlockComponentImpl:: addCommand(std::string command) {
    this->commandMutex.lock();
    U8 commandLength = command.size();
    if(commandLength > ROCKBLOCK_COMMAND_SIZE) {
        Fw::Logger::logMsg("[ERROR] RockBlock too long command: %d\n",
                           commandLength);
    } else {
        U8 newCtn = (this->commandInCtn + 1) % ROCKBLOCK_COMMAND_BUFFER_SIZE;
        if(newCtn == this->commandOutCtn) {
            Fw::Logger::logMsg("[ERROR] RockBlock sending queue full\n");
        } else {
            // ! If data are not read, they will be overriden
            sprintf(&commandBuffer[this->commandInCtn][0], command.c_str(), commandLength);
            this->commandInCtn = (this->commandInCtn + 1) % ROCKBLOCK_COMMAND_BUFFER_SIZE;
            DEBUG_PRINT("Add RockBlock command %s\n", command.c_str());
        }
    }
    this->commandMutex.unLock();
}

void RockBlockComponentImpl:: sendNextCommand() {
    this->commandMutex.lock();
    // Send command if a new one has been stored
    if(this->commandInCtn != this->commandOutCtn) {
        std::string cmd(&commandBuffer[this->commandOutCtn][0]);
        // Increment out counter if command has been sent
        if(this->sendRockBlockCommand(cmd)) {
            this->commandOutCtn = (this->commandOutCtn + 1) % ROCKBLOCK_COMMAND_BUFFER_SIZE;
        }
    } else {
        // DEBUG_PRINT("No pending command\n");
    }
    this->commandMutex.unLock();
}

bool RockBlockComponentImpl:: sendRockBlockCommand(std::string command) {
    serialMutex.lock();
    bool sent = false;
    if(this->rockBlockIsOk) {
        this->rockBlockIsOk = false;    // @todo Check concurrency, mutex ?
        char commandToSend[30]; 
        Fw::Buffer buffer;
        U16 size = command.size() + 1;

        sprintf(commandToSend, "%s\r", command.c_str());
        buffer.setData((U8*)commandToSend);
        buffer.setSize(size);
        this->serialSend_out(0, buffer);

        Fw::LogStringArg arg(command.c_str());
        this->log_DIAGNOSTIC_RckBlck_CommandSent(arg);
        sent = true;
    } else {
        DEBUG_PRINT("RockBlock is not ok, delay command %s\n", command.c_str());
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
    // @todo Implement Ping logic
    PingOut_out(0, key);
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
            Fw::LogStringArg arg("OK");
            this->log_DIAGNOSTIC_RckBlck_Response(arg);
            // Send next command when last command ack received
            this->sendNextCommand();
            //this->addCommand("AT+CSQ"); // @todo send CSQ request in loop, debug purpose
        } else if(detectCommand("ERROR", pointer)) {
            Fw::LogStringArg arg("ERROR");
            this->log_DIAGNOSTIC_RckBlck_Response(arg);
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
                        this->addCommand("AT+SBDRT");
                        break;
                    case 2:
                        this->log_WARNING_HI_RckBlck_MailboxCheckFail();
                        break;
                }
            } else {
                Fw::Logger::logMsg("[ERROR] Unable to parse SBDIX RockBlock response, res=%u\n", res);
            }
        } else if(detectCommand("+SBDRT:", pointer)) {
            this->dataReceived = true;
            // Data received are received on next line and will be processed below
            printf("[RockBlock] +SBDRT:\n");
        } else if (detectCommand("SBDRING", pointer)) {
            this->log_ACTIVITY_HI_RckBlck_RingAlert();
            this->addCommand("AT+SBDIXA");
        } else if(detectCommand("\r\n", pointer) && buffsize == 2) {
            // Empty line
            //DEBUG_PRINT("[RockBlock] Emtpy\n", pointer);
        } else {
            if(this->dataReceived) {
                DEBUG_PRINT("[RockBlock] %s\n", pointer);
                if(SBDIX.mtQueued > 0) {
                    // @todo send next SBDIX request (or SBDRT ?) to get remaining messages
                    continue;
                }
                /*/ @todo process rx data
                U8* data = this->m_buffer.getData();
                FW_ASSERT(data);

                this->m_buffer.setSize(size);
                this->recvData(this->m_buffer);
                //*/ 
            } else {
                Fw::LogStringArg arg(pointer);
                this->log_DIAGNOSTIC_RckBlck_Response(arg);
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
