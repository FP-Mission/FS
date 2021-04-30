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

    /*/ Modes
    [{'implicit': 0, 'coding': 8, 'bandwidth': 3, 'spreading': 11, 'lowopt': 1},  # 0
    {'implicit': 1, 'coding': 5, 'bandwidth': 3, 'spreading':  6, 'lowopt': 0},  # 1
    {'implicit': 0, 'coding': 8, 'bandwidth': 6, 'spreading':  8, 'lowopt': 0},  # 2
    {'implicit': 0, 'coding': 6, 'bandwidth': 8, 'spreading':  7, 'lowopt': 0},  # 3
    {'implicit': 1, 'coding': 5, 'bandwidth': 8, 'spreading':  6, 'lowopt': 0},  # 4
    {'implicit': 0, 'coding': 8, 'bandwidth': 5, 'spreading': 11, 'lowopt': 0},  # 5
    {'implicit': 1, 'coding': 5, 'bandwidth': 5, 'spreading':  6, 'lowopt': 0}]  # 6
    //*/
    mode = 0;
    frequency = 434.225;

    modes[0].implicit = 0;
    modes[0].coding = 8;
    modes[0].bandwidth = 3;
    modes[0].spreading = 11;
    modes[0].lowopt = 1;

    modes[1].implicit = 1;
    modes[1].coding = 5;
    modes[1].bandwidth = 3;
    modes[1].spreading = 6;
    modes[1].lowopt = 0;

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
    *(pointer + buffsize) = '\0';
    DEBUG_PRINT("[FlexTrak] Rx (%u): %s\n", buffsize, pointer);

    // Return buffer (see above note)
    serBuffer.setSize(UART_READ_BUFF_SIZE);
    this->serialBufferOut_out(0, serBuffer);
}

void FlexTrakComponentImpl ::sendData_handler(const NATIVE_INT_TYPE portNum,
                                              Fw::Buffer &fwBuffer) {
    char *pointer = reinterpret_cast<char *>(fwBuffer.getData());

    U16 packetSize = fwBuffer.getSize();

    DEBUG_PRINT("sendData_handler buffer size %u\n", packetSize);

    if(packetSize > FW_COM_BUFFER_MAX_SIZE) {
        printf("[FlexTrak] Too big packet\n");
        return;
        // @todo Implement event (?)
    }

    sendFlexTrakCommand("CH1");

    /*/ Hex test
    char data[31];
    data[0] = '~';
    data[1] = 'L';
    data[2] = 'D';

    data[3] = 3;
    data[4] = 0xAB;
    data[5] = 0xCD;
    data[6] = 0xEF;
    data[7] = '\r';

    U8 commandSize = 8;
    //*/

    // 
    char data[FW_COM_BUFFER_MAX_SIZE + 5]; // 
    data[0] = '~';
    data[1] = 'L';
    data[2] = 'D';
    data[3] = packetSize;
    U8 i = 0;
    printf("[FlexTrak] Downlink data");
    for (i; i < packetSize; i++) {
        data[4 + i] = *(pointer + i);
        // printf("%X", data[4 + i]);
    }
    printf("\n");
    data[packetSize + 4] = '\r';
    U8 commandSize = packetSize + 5;
    //*/


    Fw::Buffer buf; 
    buf.setData((U8*)data);
    buf.setSize(commandSize);
    
    sendFlexTrak(buf);
    //*/

    /*/ Coucou test
    static U8 cnt = 0;
    char data[100];
    sprintf(data, "LMCoucou%u", cnt);
    cnt++;
    sendFlexTrakCommand(data);
    //*/

    //char data[] = "~CV\r";  // 4
    sendFlexTrakCommand("CH0");

}

void FlexTrakComponentImpl:: sendFlexTrak(Fw::Buffer &buffer) {
    DEBUG_PRINT("[FlexTrak] Tx (%u)\n", buffer.getSize());
    this->serialSend_out(0, buffer);
}

void FlexTrakComponentImpl:: sendFlexTrakCommand(std::string command) {
    char commandToSend[30]; 
    Fw::Buffer buffer;
    U16 size = command.size() + 2;

    sprintf(commandToSend, "~%s\r", command.c_str());
    buffer.setData((U8*)commandToSend);
    buffer.setSize(size);
    // sendFlexTrak(buf); // directly call serialSend_out() to avoid sendFlexTrak() log
    this->serialSend_out(0, buffer);
    DEBUG_PRINT("[FlexTrak] Tx (%u) ~s%s\n", size, command.c_str());
}

void FlexTrakComponentImpl:: configureHardware() {
    char temp[20]; 
    // ensure array is big enough to contain command, parameters and additional 
    // '\r' added by sendFlexTrakCommand()
    sendFlexTrakCommand("CH0"); // Low priority mode
    sendFlexTrakCommand("CV");  // Ask version
    sendFlexTrakCommand("CPFP1");   // Set payload name to FP1
    // Set LoRa parameters
    sprintf(temp, "LI%u", modes[mode].implicit);
    sendFlexTrakCommand(temp);
    sprintf(temp, "LE%u", modes[mode].coding);
    sendFlexTrakCommand(temp);
    sprintf(temp, "LB%u", modes[mode].bandwidth);
    sendFlexTrakCommand(temp);
    sprintf(temp, "LS%u", modes[mode].spreading);
    sendFlexTrakCommand(temp);
    sprintf(temp, "LL%u", modes[mode].lowopt);
    sendFlexTrakCommand(temp);
    sprintf(temp, "LF%.3f", frequency);
    sendFlexTrakCommand(temp);
    sendFlexTrakCommand("CS");  // Save settings
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
