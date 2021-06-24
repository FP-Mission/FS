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
#include <Fw/Com/ComPacket.hpp>
#include <Svc/GroundInterface/GroundInterface.hpp>

#include "Fw/Logger/Logger.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/EightyCharString.hpp"
#include "Fw/Com/ComBuffer.hpp"

#include <stdio.h>
#include <stdlib.h>

//#define DEBUG_PRINT(x,...) Fw::Logger::logMsg(x,##__VA_ARGS__);
#define DEBUG_PRINT(x,...)

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
    this->mode = 1;
    this->frequency = 434.225;

    this->modes[0].implicit = 0;
    this->modes[0].coding = 8;
    this->modes[0].bandwidth = 3;
    this->modes[0].spreading = 11;
    this->modes[0].lowopt = 1;

    this->modes[1].implicit = 1;
    this->modes[1].coding = 5;
    this->modes[1].bandwidth = 3;
    this->modes[1].spreading = 6;
    this->modes[1].lowopt = 0;

    this->tlmPacketInCtn = 0;
    this->tlmPacketOutCtn = 0;
    this->logPacketInCtn = 0;
    this->logPacketOutCtn = 0;

    this->lastTlmReportTime = Fw::Time(0, 0);
    this->newPicturePacket = false;
    this->newTlmReport = false;
}

// Step 0: The linux serial driver keeps its storage externally. This means that
// we need to supply it some buffers to
//        work with. This code will loop through our member variables holding
//        the buffers and send them to the linux serial driver.  'preamble' is
//        automatically called after the system is constructed, before the
//        system runs at steady-state. This allows for initialization code that
//        invokes working ports.
void FlexTrakComponentImpl::preamble(void) {
    // LoRa is considered as free on init
    this->loRaIsFree = true;
    // Default ping key value
    this->pingKey = 0;
    // Create queue to store packets to downlink
    Fw::EightyCharString queueName("downlink");
    this->downlinkQueue.create(queueName, 10, Fw::ComBuffer::SERIALIZED_SIZE);

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
    // Save ping key to allow response in serialRecv_handler
    pingMutex.lock();
    this->pingKey = key;
    pingMutex.unLock();
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
        Fw::Logger::logMsg("[ERROR] FlexTrak serial received error: %d\n",
                           status);

        serBuffer.setSize(UART_READ_BUFF_SIZE);
        this->serialBufferOut_out(0, serBuffer);
        return;
    }
    // Make sure end of char is '\0'
    *(pointer + buffsize) = '\0';

    // Ping response sent each time ping request was received
    pingMutex.lock();
    if(this->pingKey != 0) {
        PingOut_out(0, this->pingKey);
        this->pingKey = 0;

    }
    pingMutex.unLock();

    try {
        if(detectCommand("*", pointer)) {               // Command ack by the AVR
            DEBUG_PRINT("[FlexAvr] Ack %s", reinterpret_cast<POINTER_CAST>(pointer + 1));
        } else if(detectCommand("?", pointer)) {        // Command error response AVR
            DEBUG_PRINT("[FlexAvr] Command error %s", reinterpret_cast<POINTER_CAST>(pointer + 1));
        } else if (detectCommand("GPS=", pointer)) {
            // GPS=18/05/2021,08:43:32,46.22469,7.38071,0,3
            struct GPS_t {
                I16 day, month, year;
                U8 hours, minutes, seconds;
                float latitude, longitude;
                U16 altitude;
                U8 satellites;
            } GPS;

            U8 res = 0;
            res = sscanf(pointer + 4, "%d/%d/%d,%u:%u:%u,%f,%f,%u,%u", 
                                        &GPS.day, &GPS.month, &GPS.year, 
                                        &GPS.hours, &GPS.minutes, &GPS.seconds, 
                                        &GPS.latitude, &GPS.longitude, &GPS.altitude, 
                                        &GPS.satellites);

            if(res == 10) {
                //DEBUG_PRINT("%u:%u:%u le %d.%d.%d à (%f, %f, %u) : %u\n", GPS.hours, GPS.minutes, GPS.seconds, GPS.day, GPS.month, GPS.year, GPS.latitude, GPS.longitude, GPS.altitude, GPS.satellites);
                // @todo Set FS time with received data
                Fw::Time time = getTime();
                this->gps_out(0, time, GPS.latitude, GPS.longitude, GPS.altitude, GPS.satellites);
            } else {
                Fw::Logger::logMsg("[ERROR] Unable to parse GPS FlexTrak response, res=%u\n", res);
            }
        } else if(detectCommand("Batt=", pointer)) {
            I16 batteryVoltage = atoi(pointer + 5);
            batteryVoltage_out(0, (U16)batteryVoltage);
        }  else if(detectCommand("Temp0=", pointer)) {
            I16 temp0 = atoi(pointer + 6);
            internalTemp_out(0, temp0);
        }  else if(detectCommand("Temp1=", pointer)) {
            I16 temp1 = atoi(pointer + 6);
            externalTemp_out(0, temp1);
        } else if(detectCommand("LoRaIsFree=", pointer)) {
            loRaIsFreeMutex.lock();
            this->loRaIsFree = atoi(pointer + 11) == 1 ? true : false;
            if(this->loRaIsFree) {
                DEBUG_PRINT("[FlexAvr] LoRa freed\n");
            } else {
                DEBUG_PRINT("[FlexAvr] LoRa busy\n");
            }
            loRaIsFreeMutex.unLock();
        } else if(detectCommand("DataDownlinked=", pointer)) {
            DEBUG_PRINT("[FlexAvr] Data downlinked (%u)\n", atoi(pointer + 15));
        } else {
            DEBUG_PRINT("[FlexAvr] Rx (%u): %s", buffsize, reinterpret_cast<POINTER_CAST>(pointer));
        }
    } catch (...) {
        Fw::Logger::logMsg("[ERROR] Unable to decode frame received from FlexAvr\n");
    }

    // Return buffer (see above note)
    serBuffer.setSize(UART_READ_BUFF_SIZE);
    this->serialBufferOut_out(0, serBuffer);
}

bool FlexTrakComponentImpl ::detectCommand(const char* command, const char* line) {
    bool found = true;
    for (int i = 0; i < strlen(command); i++) {
        found &= (command[i] == line[i]);
    }
    return found;
}

void FlexTrakComponentImpl ::sendData_handler(const NATIVE_INT_TYPE portNum,
                                              Fw::Buffer &buffer) {
    TOKEN_TYPE token;
    TOKEN_TYPE dataSize;
    FwPacketDescriptorType packetType;
    char *pointer = reinterpret_cast<char *>(buffer.getData());

    U16 packetSize = buffer.getSize();

    if(packetSize > FW_COM_BUFFER_MAX_SIZE) {
        Fw::Logger::logMsg("[ERROR] Too big packet to downlink %u\n", packetSize);
        return;
        // @todo Implement event (?)
    }
    
    //Deserialize packet to know if it is events/telemetry/camera
    Fw::SerializeBufferBase& deserBufferWrapper = buffer.getSerializeRepr();
    deserBufferWrapper.resetDeser();
    deserBufferWrapper.setBuffLen(buffer.getSize());

    Fw::SerializeStatus stat = deserBufferWrapper.deserialize(token);
    FW_ASSERT(Fw::FW_SERIALIZE_OK == stat,static_cast<NATIVE_INT_TYPE>(stat));
    FW_ASSERT(token == Svc::GroundInterfaceComponentImpl::START_WORD);

    stat = deserBufferWrapper.deserialize(dataSize);
    FW_ASSERT(Fw::FW_SERIALIZE_OK == stat,static_cast<NATIVE_INT_TYPE>(stat));

    stat = deserBufferWrapper.deserialize(packetType);
    FW_ASSERT(Fw::FW_SERIALIZE_OK == stat,static_cast<NATIVE_INT_TYPE>(stat));

    if(packetType == Fw::ComPacket::FW_PACKET_LOG) {
        // Save log packet for downlink
        if(packetSize <= FW_COM_BUFFER_MAX_SIZE) {
            this->lastLogPacketsMutex.lock();
            U8 newCtn = (this->logPacketInCtn + 1) % LOG_PACKETS_QUEUE_SIZE;
            if(newCtn == this->logPacketOutCtn) {
                Fw::Logger::logMsg("[ERROR] Unable to store LogPacket for downlink - Queue full\n");
            } else {
                memcpy(&lastLogPackets[this->logPacketInCtn][0], pointer, packetSize);
                this->lastLogPacketsSize[this->logPacketInCtn] = packetSize;
                DEBUG_PRINT("[FlexTrak] LogPacket (%u) saved for downlink (%u)\n", packetSize, this->logPacketInCtn);
                this->logPacketInCtn = newCtn;
            }
            this->lastLogPacketsMutex.unLock();
        } else {
            Fw::Logger::logMsg("[ERROR] LogPacket too big (%u) - Unable to store it for downlink\n", packetSize);
        }
    } else if (packetType == Fw::ComPacket::FW_PACKET_TLM_REPORT) {
        // Save TlmReportPacket for downlink
        if(packetSize == TLM_REPORT_SIZE) {
            this->lastTlmReportMutex.lock();
            memcpy(this->lastTlmReport, pointer, packetSize);
            this->newTlmReport = true;
            this->lastTlmReportMutex.unLock();
            DEBUG_PRINT("[FlexTrak] TlmReportPacket saved for downlink (%u)\n", buffer.getSize());
        } else {
            Fw::Logger::logMsg("[ERROR] Incorrect size for TlmReportPacket (%u) - Unable to store it for downlink\n", packetSize);
        }
    } else if (packetType == Fw::ComPacket::FW_PACKET_TELEM) {
        // Save TlmPacket for downlink
        if(packetSize <= FW_COM_BUFFER_MAX_SIZE) {
            this->lastTlmPacketsMutex.lock();
            U8 newCtn = (this->tlmPacketInCtn + 1) % TLM_PACKETS_QUEUE_SIZE;
            if(newCtn == this->tlmPacketOutCtn) {
                Fw::Logger::logMsg("[ERROR] Unable to store TlmPacket for downlink - Queue full\n");
            } else {
                memcpy(&lastTlmPackets[this->tlmPacketInCtn][0], pointer, packetSize);
                this->lastTlmPacketsSize[this->tlmPacketInCtn] = packetSize;
                DEBUG_PRINT("[FlexTrak] TlmPacket (%u) saved for downlink (%u)\n", packetSize, this->tlmPacketInCtn);
                this->tlmPacketInCtn = newCtn;
            }
            this->lastTlmPacketsMutex.unLock();
        } else {
            Fw::Logger::logMsg("[ERROR] TlmPacket too big (%u) - Unable to store it for downlink\n", packetSize);
        } 
    } else if (packetType == Fw::ComPacket::FW_PACKET_PICTURE) {
        // Save PicturePacket for downlink
        if(packetSize <= PICTURE_PACKET_SIZE) {
            this->lastPicturePacketMutex.lock();
            memcpy(this->lastPicturePacket, pointer, packetSize);
            this->lastPictureSize = packetSize;
            this->newPicturePacket = true;
            this->lastPicturePacketMutex.unLock();
            DEBUG_PRINT("[FlexTrak] PicturePacket saved for downlink (%u)\n", buffer.getSize());
        } else {
            Fw::Logger::logMsg("[ERROR] PicturePacket too big (%u) - Unable to store it for downlink\n", packetSize);
        }
    }
}

void FlexTrakComponentImpl::Run_handler(NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    this->loRaIsFreeMutex.lock();
    bool loRaIsFree_cpy = this->loRaIsFree;
    this->loRaIsFreeMutex.unLock();
    if(loRaIsFree_cpy) {
        DEBUG_PRINT("DownlinkDataScheduler called\n");
        downlinkDataScheduler();
    } else {
        DEBUG_PRINT("DownlinkDataScheduler not called, LoRa is busy\n");
    }
}

void FlexTrakComponentImpl::downlinkDataScheduler() {
    bool ret = false;

    // PRIORITY 4 (forced)
    // Force send TlmReport if none has been sent since 20 seconds
    this->lastTlmReportMutex.lock();
    
    Fw::Time currentTime = getTime();
    Fw::Time delta = Fw::Time::sub(currentTime, this->lastTlmReportTime);

    if(this->newTlmReport && delta.getSeconds() > 20) {
        Fw::Logger::logMsg("[INFO] Downlink TlmReport (forced after %u seconds)\n", delta.getSeconds());
        if(downlinkData(this->lastTlmReport, TLM_REPORT_SIZE)) {
            this->lastTlmReportTime = getTime();
            this->newTlmReport = false;
        }
        ret = true;
    }
    this->lastTlmReportMutex.unLock();

    if(ret) return;
    
    // PRIORITY 1 
    // Send LogPacket if available
    this->lastLogPacketsMutex.lock();
    if(this->logPacketInCtn != this->logPacketOutCtn) {
        U16 packetSize = this->lastLogPacketsSize[this->logPacketOutCtn];
        Fw::Logger::logMsg("[INFO] Downlink LogPacket (%u, %u)\n", packetSize, this->logPacketOutCtn);
        if(downlinkData(&this->lastLogPackets[this->logPacketOutCtn][0], packetSize)) {
            this->logPacketOutCtn = (this->logPacketOutCtn + 1) % LOG_PACKETS_QUEUE_SIZE;
        }
        ret = true;
    }
    this->lastLogPacketsMutex.unLock();

    if(ret) return;

    // PRIORITY 2
    // Send TlmPacket if available
    this->lastTlmPacketsMutex.lock();
    if(this->tlmPacketInCtn != this->tlmPacketOutCtn) {
        U16 packetSize = this->lastTlmPacketsSize[this->tlmPacketOutCtn];
        Fw::Logger::logMsg("[INFO] Downlink TlmPacket (%u, %u)\n", packetSize, this->tlmPacketOutCtn);
        if(downlinkData(&this->lastTlmPackets[this->tlmPacketOutCtn][0], packetSize)) {
            this->tlmPacketOutCtn = (this->tlmPacketOutCtn + 1) % TLM_PACKETS_QUEUE_SIZE;
        }
        ret = true;
    }
    this->lastTlmPacketsMutex.unLock();

    if(ret) return;


    // PRIORITY 3
    // Send PicturePacket if available
    this->lastPicturePacketMutex.lock();
    if(this->newPicturePacket) {
        Fw::Logger::logMsg("[INFO] Downlink PicturePacket (%u)\n", this->lastPictureSize);
        if(downlinkData(this->lastPicturePacket, this->lastPictureSize)) {
            this->newPicturePacket = false;
            // Ask next PicturePacket
            this->AskPictureFrame_out(0, 0);
        }
        ret = true;
    }
    this->lastPicturePacketMutex.unLock();

    if(ret) return;

    // PRIORITY 4
    // Send TlmReport if available
    this->lastTlmReportMutex.lock();
    if(this->newTlmReport) {
        Fw::Logger::logMsg("[INFO] Downlink TlmReport\n");
        if(downlinkData(this->lastTlmReport, TLM_REPORT_SIZE)) {
            this->lastTlmReportTime = getTime();
            this->newTlmReport = false;
        }
    }
    this->lastTlmReportMutex.unLock();
}

bool FlexTrakComponentImpl::downlinkData(char *packetPointer, U16 packetSize) {
    bool dataDownlinked = false;

    this->loRaIsFreeMutex.lock();
    bool loRaIsFree_cpy = this->loRaIsFree;
    this->loRaIsFreeMutex.unLock();

    if(loRaIsFree_cpy) {
        sendFlexTrakCommand("CH1");

        char data[FW_COM_BUFFER_MAX_SIZE + 5]; // Add header and tail ~LD<size>[... packet ...]'\r'
        data[0] = '~';
        data[1] = 'L';
        data[2] = 'D';
        data[3] = packetSize;
        U8 i = 0;
        //DEBUG_PRINT("Downlink data : ");
        for (i; i < packetSize; i++) {
            data[4 + i] = *(packetPointer + i);
            //DEBUG_PRINT("%2X", data[4 + i]);
        }
        //DEBUG_PRINT("\n");
        data[packetSize + 4] = '\r';    
        // @todo Should not be necessary, but current binary mode in FlexTrak use \r after binary data receiption
        // to process command. Incorrect way to deal with it but it works, so .... u know

        U8 commandSize = packetSize + 5;
        //*/

        Fw::Buffer buf; 
        buf.setData((U8*)data);
        buf.setSize(commandSize);

        sendFlexTrak(buf);

        sendFlexTrakCommand("CH0");

        dataDownlinked = true;
    } else {
        Fw::Logger::logMsg("[ERROR] FlexTrak is not ready to downlink data - Abord\n");
    }

    return dataDownlinked;
}

void FlexTrakComponentImpl:: sendFlexTrak(Fw::Buffer &buffer) {
    serialMutex.lock();
    DEBUG_PRINT("FlexTrak Tx (%u) %.3s\n", buffer.getSize(), reinterpret_cast<POINTER_CAST>(buffer.getData()));
    this->serialSend_out(0, buffer);
    serialMutex.unLock();
}

void FlexTrakComponentImpl:: sendFlexTrakCommand(std::string command) {
    serialMutex.lock();
    char commandToSend[30]; 
    Fw::Buffer buffer;
    U16 size = command.size() + 2;

    sprintf(commandToSend, "~%s\r", command.c_str());
    buffer.setData((U8*)commandToSend);
    buffer.setSize(size);
    // sendFlexTrak(buf); // directly call serialSend_out() to avoid sendFlexTrak() log
    this->serialSend_out(0, buffer);
    DEBUG_PRINT("FlexTrak Tx (%u) ~%s\n", size, reinterpret_cast<POINTER_CAST>(command.c_str()));
    serialMutex.unLock();
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


void FlexTrakComponentImpl :: FT_CHANGE_MODE_cmdHandler(
    const FwOpcodeType opCode,
    const U32 cmdSeq,
    U8 mode
){
    if(mode == 0 || mode == 1) {
        this->mode = mode;
        this->configureHardware();
        this->log_ACTIVITY_HI_FT_Mode(mode);
        this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
        return;
    }
    Fw::Logger::logMsg("[ERROR] Invalid mode for LoRa: %u - Please use 0 or 1\n", mode);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_EXECUTION_ERROR);
}

void FlexTrakComponentImpl :: FT_CHANGE_FREQ_cmdHandler(
    const FwOpcodeType opCode,
    const U32 cmdSeq,
    F32 frequency 
){
    if(frequency >= LORA_MIN_FREQUENCY && frequency <= LORA_MAX_FREQUENCY) {
        this->frequency = frequency;
        this->configureHardware();
        this->log_ACTIVITY_HI_FT_Frequency(frequency);
        this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
        return;
    }
    Fw::Logger::logMsg("[ERROR] Invalid frequency for LoRa : %f\n", 
                        frequency);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_EXECUTION_ERROR);
}

}  // end namespace App
