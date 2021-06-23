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

#define ROCKBLOCK_COMMAND_SIZE 16
#define ROCKBLOCK_COMMAND_BUFFER_SIZE 10    // Maximum allocation size for RockBlock AT commands
#define FP_COMMAND_BUFFER_SIZE 128          // Maximum allocation size of the recv buffer for F' commands

#define MAILBOX_INTERVAL 900 // (300) seconds, set to 0 to disable. if enabled, will periodically check mailbox (+ at launch)
#define CSQ_INTERVAL 4

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

    //!  \brief run handler
    //!
    //!  Handler implementation for run
    //!
    //!  \param portNum Port number
    //!  \param context Port Context
    void Run_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context);

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

    void addCommand(std::string command);
    void sendNextCommand();
    bool sendRockBlockCommand(std::string command, bool log);
    bool sendRockBlockCommand(std::string command);
    bool detectCommand(const char* command, const char* line);
    U8 HexToByte(char hex);

    // ----------------------------------------------------------------------
    // Command handler implementations
    // ----------------------------------------------------------------------

    //! Implementation for RckBlck_SendCommand command handler
    //! Sample command
    void RckBlck_SendCommand_cmdHandler(
        const FwOpcodeType opCode, /*!< The opcode*/
        const U32 cmdSeq, /*!< The command sequence number*/
        const Fw::CmdStringArg& AT_Command, /*!< AT command to send */ 
        const U8 mode /*!< Mode - 0: send command, 1: add command to buffer */
    );

    // Serial buffer provider to LinuxSerialDriver
    Fw::Buffer m_serialRecvBuffers[DR_MAX_NUM_BUFFERS];
    BYTE m_serialRecvData[DR_MAX_NUM_BUFFERS][UART_READ_BUFF_SIZE];

    Os::Mutex serialMutex;      //<! Locked when serial line is used
    Os::Mutex rbCommandMutex;   //<! Protect rbCommandBuffer when used
    bool rockBlockIsOk;         //<! Indicates when RockBlock can receive new AT command

    // Circual buffer to store AT commands to send to the RockBlock module
    char rbCommandBuffer[ROCKBLOCK_COMMAND_BUFFER_SIZE][ROCKBLOCK_COMMAND_SIZE];
    U8 rbCommandInCtn;
    U8 rbCommandOutCtn;

    Fw::Buffer fpCommandBuffer;                 //!< Buffer used to pass F' commands received by RockBlock
    U8 fpCommandData[FP_COMMAND_BUFFER_SIZE];   //!< Data for above buffer

    bool textDataReceived;  //!< Set to True when next line is RX text data
    
    struct SBDIX_t {
        U8 moStatus;
        U16 moMsn;
        U8 mtStatus;
        U16 mtMsn;
        U16 mtLength;
        U16 mtQueued;
    } SBDIX;

    U32 pingKey;            //<! Save pingKey on pingIn
    U8 pingCtn;
    Os::Mutex pingMutex;    //<! Mutual exclusion between PingIn_handler and serialRecv_handler

    Os::Mutex mailboxCheckMutex;    //<! Mutual exclusion for mailbox check time

    Fw::Time lastMailboxCheck;

    public:
        bool simulatorMode;
};

}  // end namespace App

#endif
