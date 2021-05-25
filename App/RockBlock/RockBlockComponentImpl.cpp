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
    : RockBlockComponentBase(compName) {}

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
    // RockBlock is considered as available at launch
    this->rockBlockIsOk = true;
    for (NATIVE_INT_TYPE buffer = 0; buffer < DR_MAX_NUM_BUFFERS; buffer++) {
        // Assign the raw data to the buffer. Make sure to include the side of
        // the region assigned.
        this->m_recvBuffers[buffer].setData(this->m_uartBuffers[buffer]);
        this->m_recvBuffers[buffer].setSize(UART_READ_BUFF_SIZE);
        // Invoke the port to send the buffer out.
        this->serialBufferOut_out(0, this->m_recvBuffers[buffer]);
    }
}

RockBlockComponentImpl ::~RockBlockComponentImpl(void) {}

void RockBlockComponentImpl:: configureHardware() {
    char temp[20];
    this->sendRockBlockCommand("AT");
    sleep(1);
    this->sendRockBlockCommand("AT+SBDMTA?");
    sleep(1);
    this->sendRockBlockCommand("AT+CSQ");
}

void RockBlockComponentImpl:: sendRockBlockCommand(std::string command) {
    serialMutex.lock();
    if(this->rockBlockIsOk) {
        this->rockBlockIsOk = false;    // @todo Check concurrency, mutex ?
        char commandToSend[30]; 
        Fw::Buffer buffer;
        U16 size = command.size() + 1;

        sprintf(commandToSend, "%s\r", command.c_str());
        buffer.setData((U8*)commandToSend);
        buffer.setSize(size);
        this->serialSend_out(0, buffer);
        DEBUG_PRINT("[RockBlock] Tx (%u) %s\n", size, command.c_str());
    } else {
        // @todo Replace by queue
        DEBUG_PRINT("RockBlock is not ok, abord command %s\n", command.c_str());
    }
    serialMutex.unLock();
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
    const U32 cmdSeq
    //const Fw::CmdStringArg& AT_Command
) {
    //std::string str(AT_Command.toChar());
    //printf("Send %s\n", str.c_str());
    this->sendRockBlockCommand("AT+SBDIX");
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
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
            DEBUG_PRINT("[RockBlock] OK\n");
        } else if(detectCommand("+CSQ:", pointer)) {
            U8 signalQuality = atoi(pointer + 5);
            
            DEBUG_PRINT("[RockBlock] +CSQ: %u\n", signalQuality);
        } else if(detectCommand("+SBDMTA:", pointer)) {
            U8 ringAllertEnabled = atoi(pointer + 8);
            if(ringAllertEnabled) {
                DEBUG_PRINT("[RockBlock] Ring alert enabled\n");
            } else {
                DEBUG_PRINT("[RockBlock] Ring alert disabled\n");
            }
        } else if(detectCommand("+SBDIX:", pointer)) {
            struct SBDIX_t {
                U8 moStatus;
                U16 moMsn;
                U8 mtStatus;
                U16 mtMsn;
                U16 mtLength;
                U16 mtQueued;
            } SBDIX;

            U8 res = 0;
            res = sscanf(pointer + 8, "%u, %u, %u, %u, %u, %u", 
                                        &SBDIX.moStatus, &SBDIX.moMsn,
                                        &SBDIX.mtStatus, &SBDIX.mtMsn,
                                        &SBDIX.mtLength, &SBDIX.mtQueued);

            if(res == 6) {
                DEBUG_PRINT("[RockBlock] moStatus: %u, moMsN: %u, mtStatus: %u, mtMsn: %u, mtLength: %u, mtQueued: %u\n", 
                                SBDIX.moStatus, SBDIX.moMsn, SBDIX.mtStatus, SBDIX.mtMsn, SBDIX.mtLength, SBDIX.mtQueued);

                if(SBDIX.moStatus >= 0 && SBDIX.moStatus <= 2) {
                    DEBUG_PRINT("[RockBlock] Message, if any, transferred successfully (%u)\n", SBDIX.moMsn);
                } else {
                    Fw::Logger::logMsg("[ERROR] Unable to send RockBlock message\n");
                }

                switch (SBDIX.mtStatus) {
                    case 0:
                        // No SBD message to receive from the GSS
                        break;
                    case 1:
                        // SBD message successfully received from the GSS.
                        DEBUG_PRINT("[RockBlock] Message %u received (%u pending)\n", SBDIX.mtMsn);
                        this->sendRockBlockCommand("AT+SBDRT");
                        break;
                    case 2:
                        Fw::Logger::logMsg("[ERROR] Unable to check RockBlock mailbox or receive message from GSS\n");
                        break;
                }
            } else {
                Fw::Logger::logMsg("[ERROR] Unable to parse SBDIX RockBlock response, res=%u\n", res);
            }
        } else if(detectCommand("+SBDRT:", pointer)) {
            printf("[RockBlock] %s\n", pointer);
        } else if (detectCommand("SBDRING", pointer)) {
            DEBUG_PRINT("[RockBlock] SBDRING\n");
        } else if(detectCommand("\r\n", pointer) && buffsize == 2) {
            // Empty line
            //DEBUG_PRINT("[RockBlock] Emtpy\n", pointer);
        } else {
            DEBUG_PRINT("[RockBlock] Rx (%u): %s\n", buffsize, pointer);
        }
    } catch (...) {
        Fw::Logger::logMsg("[ERROR] Unable to decode frame received from FlexAvr\n");
    }


    // Return buffer (see above note)
    serBuffer.setSize(UART_READ_BUFF_SIZE);
    this->serialBufferOut_out(0, serBuffer);
}

}  // end namespace App
