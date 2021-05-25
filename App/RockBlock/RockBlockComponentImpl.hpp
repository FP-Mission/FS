// ======================================================================
// \title  RockBlockComponentImpl.hpp
// \author jonathan
// \brief  hpp file for RockBlock component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef RockBlock_HPP
#define RockBlock_HPP

#include <Os/Mutex.hpp>

#include "App/RockBlock/RockBlockComponentAc.hpp"
#include "fprime/config/LinuxSerialDriverComponentImplCfg.hpp"

#include <string>

namespace App {

class RockBlockComponentImpl : public RockBlockComponentBase {
   public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object RockBlock
    //!
    RockBlockComponentImpl(const char *const compName /*!< The component name*/
    );

    //! Initialize object RockBlock
    //!
    void init(const NATIVE_INT_TYPE queueDepth,  /*!< The queue depth*/
              const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Preamble
    //!
    void preamble(void);

    //! Destroy object RockBlock
    //!
    ~RockBlockComponentImpl(void);

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

    void sendRockBlockCommand(std::string command);
    bool detectCommand(const char* command, const char* line);

    // ----------------------------------------------------------------------
    // Command handler implementations
    // ----------------------------------------------------------------------

    //! Implementation for RckBlck_SendCommand command handler
    //! Sample command
    void RckBlck_SendCommand_cmdHandler(
        const FwOpcodeType opCode, /*!< The opcode*/
        const U32 cmdSeq /*!< The command sequence number*/
        //const Fw::CmdStringArg& AT_Command /*!< AT command to send */ 
    );

    // Serial buffer provider to LinuxSerialDriver
    Fw::Buffer m_recvBuffers[DR_MAX_NUM_BUFFERS];
    BYTE m_uartBuffers[DR_MAX_NUM_BUFFERS][UART_READ_BUFF_SIZE];

    Os::Mutex serialMutex;    //<! Lock when serial line is used
    bool rockBlockIsOk;

};

}  // end namespace App

#endif
