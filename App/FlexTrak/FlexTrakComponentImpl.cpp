// ======================================================================
// \title  FlexTrakComponentImpl.cpp
// \author jonathan
// \brief  cpp file for FlexTrak component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <App/FlexTrak/FlexTrakComponentImpl.hpp>

#include "Fw/Logger/Logger.hpp"
#include "Fw/Types/BasicTypes.hpp"

#define DEBUG_PRINT(x, ...)   \
    printf(x, ##__VA_ARGS__); \
    fflush(stdout)
//#define DEBUG_PRINT(x,...)

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

FlexTrakComponentImpl ::FlexTrakComponentImpl(const char *const compName)
    : FlexTrakComponentBase(compName) {}

void FlexTrakComponentImpl ::init(const NATIVE_INT_TYPE queueDepth,
                                  const NATIVE_INT_TYPE instance) {
    FlexTrakComponentBase::init(queueDepth, instance);
}

// Step 0: The linux serial driver keeps its storage externally. This means that
// we need to supply it some buffers to
//        work with. This code will loop through our member variables holding
//        the buffers and send them to the linux serial driver.  'preamble' is
//        automatically called after the system is constructed, before the
//        system runs at steady-state. This allows for initialization code that
//        invokes working ports.
void FlexTrakComponentImpl::preamble(void) {
    for (NATIVE_INT_TYPE buffer = 0; buffer < DR_MAX_NUM_BUFFERS; buffer++) {
        // Assign the raw data to the buffer. Make sure to include the side of
        // the region assigned.
        this->m_recvBuffers[buffer].setData(this->m_uartBuffers[buffer]);
        this->m_recvBuffers[buffer].setSize(UART_READ_BUFF_SIZE);
        // Invoke the port to send the buffer out.
        this->serialBufferOut_out(0, this->m_recvBuffers[buffer]);
    }
}

FlexTrakComponentImpl ::~FlexTrakComponentImpl(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void FlexTrakComponentImpl ::PingIn_handler(const NATIVE_INT_TYPE portNum,
                                            U32 key) {
    // @todo Implement Ping logic
    PingOut_out(0, key);
}

void FlexTrakComponentImpl ::serialRecv_handler(const NATIVE_INT_TYPE portNum,
                                                Fw::Buffer &serBuffer,
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
        Fw::Logger::logMsg("[WARNING] Received buffer with bad packet: %d\n",
                           status);

        serBuffer.setSize(UART_READ_BUFF_SIZE);
        this->serialBufferOut_out(0, serBuffer);
        return;
    }
    char text[100];
    memcpy(text, pointer, buffsize);
    text[buffsize] = '\n';
    printf("[FlexTrak] Received buffer (%u): %s\n", buffsize, pointer);

    // Return buffer (see above note)
    serBuffer.setSize(UART_READ_BUFF_SIZE);
    this->serialBufferOut_out(0, serBuffer);
}

void FlexTrakComponentImpl ::sendData_handler(const NATIVE_INT_TYPE portNum,
                                              Fw::Buffer &fwBuffer) {
    printf("Data %u\n", fwBuffer.getSize());
    char text[] = "~CV\r\n";
    Fw::Buffer buf;
    buf.setData((U8*)text);
    buf.setSize(strlen(text));

    this->serialSend_out(0, buf);
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void FlexTrakComponentImpl ::FT_Version_cmdHandler(const FwOpcodeType opCode,
                                                   const U32 cmdSeq) {
    // @todo Implement version request
    this->log_ACTIVITY_LO_FT_Version(1);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

}  // end namespace App
