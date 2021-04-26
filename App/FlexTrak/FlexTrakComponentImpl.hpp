// ======================================================================
// \title  FlexTrakComponentImpl.hpp
// \author jonathan
// \brief  hpp file for FlexTrak component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FlexTrak_HPP
#define FlexTrak_HPP

#include "App/FlexTrak/FlexTrakComponentAc.hpp"
#include "fprime/config/LinuxSerialDriverComponentImplCfg.hpp"

#include <string>
#include <sstream>
#include <iostream>


namespace App {

class FlexTrakComponentImpl : public FlexTrakComponentBase {
   public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object FlexTrak
    //!
    FlexTrakComponentImpl(const char *const compName /*!< The component name*/
    );

    //! Initialize object FlexTrak
    //!
    void init(const NATIVE_INT_TYPE queueDepth,  /*!< The queue depth*/
              const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Preamble
    //!
    void preamble(void);

    //! Destroy object FlexTrak
    //!
    ~FlexTrakComponentImpl(void);
    
    void configureHardware();

    PRIVATE :

        // ----------------------------------------------------------------------
        // Handler implementations for user-defined typed input ports
        // ----------------------------------------------------------------------

        //! Handler implementation for PingIn
        //!
        void
        PingIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                       U32 key /*!< Value to return to pinger*/
        );

    //! Handler implementation for serialRecv
    //!
    void serialRecv_handler(
        const NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::Buffer &serBuffer,         /*!< Buffer containing data*/
        Drv::SerialReadStatus &status  /*!< Status of read*/
    );

    //! Handler implementation for sendData
    //!
    void sendData_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                          Fw::Buffer &fwBuffer);

    void sendFlexTrak(Fw::Buffer &buffer);
    void sendFlexTrakCommand(std::string command);


    PRIVATE :

        // ----------------------------------------------------------------------
        // Command handler implementations
        // ----------------------------------------------------------------------

        //! Implementation for FT_Version command handler
        //! Ask version
        void
        FT_Version_cmdHandler(
            const FwOpcodeType opCode, /*!< The opcode*/
            const U32 cmdSeq           /*!< The command sequence number*/
        );

    Fw::Buffer m_recvBuffers[DR_MAX_NUM_BUFFERS];
    BYTE m_uartBuffers[DR_MAX_NUM_BUFFERS][UART_READ_BUFF_SIZE];

    struct LoRaConfig {
        U8 implicit;
        U8 coding;
        U8 bandwidth;
        U8 spreading;
        U8 lowopt;
    };

    LoRaConfig modes[2];
    U8 mode;
    F32 frequency;
};

}  // end namespace App

#endif
