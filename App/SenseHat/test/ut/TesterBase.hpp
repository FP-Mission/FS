// ======================================================================
// \title  SenseHat/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for SenseHat component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SenseHat_TESTER_BASE_HPP
#define SenseHat_TESTER_BASE_HPP

#include <App/SenseHat/SenseHatComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace App {

  //! \class SenseHatTesterBase
  //! \brief Auto-generated base class for SenseHat component test harness
  //!
  class SenseHatTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object SenseHatTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect Schedin to to_Schedin[portNum]
      //!
      void connect_to_Schedin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputSchedPort *const Schedin /*!< The port*/
      );

      //! Connect PingIn to to_PingIn[portNum]
      //!
      void connect_to_PingIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputPingPort *const PingIn /*!< The port*/
      );

      //! Connect CmdDisp to to_CmdDisp[portNum]
      //!
      void connect_to_CmdDisp(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::InputCmdPort *const CmdDisp /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from SHT
      //!
      //! \return from_SHT[portNum]
      //!
      App::InputSHTPortPort* get_from_SHT(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from LPS
      //!
      //! \return from_LPS[portNum]
      //!
      App::InputLPSPortPort* get_from_LPS(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from ICM
      //!
      //! \return from_ICM[portNum]
      //!
      App::InputICMPortPort* get_from_ICM(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from PingOut
      //!
      //! \return from_PingOut[portNum]
      //!
      Svc::InputPingPort* get_from_PingOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from CmdStatus
      //!
      //! \return from_CmdStatus[portNum]
      //!
      Fw::InputCmdResponsePort* get_from_CmdStatus(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from CmdReg
      //!
      //! \return from_CmdReg[portNum]
      //!
      Fw::InputCmdRegPort* get_from_CmdReg(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from Time
      //!
      //! \return from_Time[portNum]
      //!
      Fw::InputTimePort* get_from_Time(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from Log
      //!
      //! \return from_Log[portNum]
      //!
      Fw::InputLogPort* get_from_Log(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Get the port that receives input from LogText
      //!
      //! \return from_LogText[portNum]
      //!
      Fw::InputLogTextPort* get_from_LogText(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );
#endif

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SenseHatTesterBase
      //!
      SenseHatTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SenseHatTesterBase
      //!
      virtual ~SenseHatTesterBase(void);

      // ----------------------------------------------------------------------
      // Test history
      // ----------------------------------------------------------------------

    protected:

      //! \class History
      //! \brief A history of port inputs
      //!
      template <typename T> class History {

        public:

          //! Create a History
          //!
          History(
              const U32 maxSize /*!< The maximum history size*/
          ) :
              numEntries(0),
              maxSize(maxSize)
          {
            this->entries = new T[maxSize];
          }

          //! Destroy a History
          //!
          ~History() {
            delete[] this->entries;
          }

          //! Clear the history
          //!
          void clear() { this->numEntries = 0; }

          //! Push an item onto the history
          //!
          void push_back(
              T entry /*!< The item*/
          ) {
            FW_ASSERT(this->numEntries < this->maxSize);
            entries[this->numEntries++] = entry;
          }

          //! Get an item at an index
          //!
          //! \return The item at index i
          //!
          T at(
              const U32 i /*!< The index*/
          ) const {
            FW_ASSERT(i < this->numEntries);
            return entries[i];
          }

          //! Get the number of entries in the history
          //!
          //! \return The number of entries in the history
          //!
          U32 size(void) const { return this->numEntries; }

        private:

          //! The number of entries in the history
          //!
          U32 numEntries;

          //! The maximum history size
          //!
          const U32 maxSize;

          //! The entries
          //!
          T *entries;

      };

      //! Clear all history
      //!
      void clearHistory(void);

    protected:

      // ----------------------------------------------------------------------
      // Handler prototypes for typed from ports
      // ----------------------------------------------------------------------

      //! Handler prototype for from_SHT
      //!
      virtual void from_SHT_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< sht temperature*/
          F32 humidity /*!< sht humidity*/
      ) = 0;

      //! Handler base function for from_SHT
      //!
      void from_SHT_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< sht temperature*/
          F32 humidity /*!< sht humidity*/
      );

      //! Handler prototype for from_LPS
      //!
      virtual void from_LPS_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< lps temperature*/
          F32 pressure /*!< lps humidity*/
      ) = 0;

      //! Handler base function for from_LPS
      //!
      void from_LPS_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< lps temperature*/
          F32 pressure /*!< lps humidity*/
      );

      //! Handler prototype for from_ICM
      //!
      virtual void from_ICM_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          App::Angles &angles, 
          App::Vector &gyro, 
          App::Vector &accel, 
          App::Vector &magn 
      ) = 0;

      //! Handler base function for from_ICM
      //!
      void from_ICM_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          App::Angles &angles, 
          App::Vector &gyro, 
          App::Vector &accel, 
          App::Vector &magn 
      );

      //! Handler prototype for from_PingOut
      //!
      virtual void from_PingOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      ) = 0;

      //! Handler base function for from_PingOut
      //!
      void from_PingOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Histories for typed from ports
      // ----------------------------------------------------------------------

      //! Clear from port history
      //!
      void clearFromPortHistory(void);

      //! The total number of from port entries
      //!
      U32 fromPortHistorySize;

      //! Push an entry on the history for from_SHT
      void pushFromPortEntry_SHT(
          F32 temperature, /*!< sht temperature*/
          F32 humidity /*!< sht humidity*/
      );

      //! A history entry for from_SHT
      //!
      typedef struct {
          F32 temperature;
          F32 humidity;
      } FromPortEntry_SHT;

      //! The history for from_SHT
      //!
      History<FromPortEntry_SHT>
        *fromPortHistory_SHT;

      //! Push an entry on the history for from_LPS
      void pushFromPortEntry_LPS(
          F32 temperature, /*!< lps temperature*/
          F32 pressure /*!< lps humidity*/
      );

      //! A history entry for from_LPS
      //!
      typedef struct {
          F32 temperature;
          F32 pressure;
      } FromPortEntry_LPS;

      //! The history for from_LPS
      //!
      History<FromPortEntry_LPS>
        *fromPortHistory_LPS;

      //! Push an entry on the history for from_ICM
      void pushFromPortEntry_ICM(
          App::Angles &angles, 
          App::Vector &gyro, 
          App::Vector &accel, 
          App::Vector &magn 
      );

      //! A history entry for from_ICM
      //!
      typedef struct {
          App::Angles angles;
          App::Vector gyro;
          App::Vector accel;
          App::Vector magn;
      } FromPortEntry_ICM;

      //! The history for from_ICM
      //!
      History<FromPortEntry_ICM>
        *fromPortHistory_ICM;

      //! Push an entry on the history for from_PingOut
      void pushFromPortEntry_PingOut(
          U32 key /*!< Value to return to pinger*/
      );

      //! A history entry for from_PingOut
      //!
      typedef struct {
          U32 key;
      } FromPortEntry_PingOut;

      //! The history for from_PingOut
      //!
      History<FromPortEntry_PingOut>
        *fromPortHistory_PingOut;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to Schedin
      //!
      void invoke_to_Schedin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Invoke the to port connected to PingIn
      //!
      void invoke_to_PingIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of from_SHT ports
      //!
      //! \return The number of from_SHT ports
      //!
      NATIVE_INT_TYPE getNum_from_SHT(void) const;

      //! Get the number of from_LPS ports
      //!
      //! \return The number of from_LPS ports
      //!
      NATIVE_INT_TYPE getNum_from_LPS(void) const;

      //! Get the number of from_ICM ports
      //!
      //! \return The number of from_ICM ports
      //!
      NATIVE_INT_TYPE getNum_from_ICM(void) const;

      //! Get the number of to_Schedin ports
      //!
      //! \return The number of to_Schedin ports
      //!
      NATIVE_INT_TYPE getNum_to_Schedin(void) const;

      //! Get the number of to_PingIn ports
      //!
      //! \return The number of to_PingIn ports
      //!
      NATIVE_INT_TYPE getNum_to_PingIn(void) const;

      //! Get the number of from_PingOut ports
      //!
      //! \return The number of from_PingOut ports
      //!
      NATIVE_INT_TYPE getNum_from_PingOut(void) const;

      //! Get the number of to_CmdDisp ports
      //!
      //! \return The number of to_CmdDisp ports
      //!
      NATIVE_INT_TYPE getNum_to_CmdDisp(void) const;

      //! Get the number of from_CmdStatus ports
      //!
      //! \return The number of from_CmdStatus ports
      //!
      NATIVE_INT_TYPE getNum_from_CmdStatus(void) const;

      //! Get the number of from_CmdReg ports
      //!
      //! \return The number of from_CmdReg ports
      //!
      NATIVE_INT_TYPE getNum_from_CmdReg(void) const;

      //! Get the number of from_Time ports
      //!
      //! \return The number of from_Time ports
      //!
      NATIVE_INT_TYPE getNum_from_Time(void) const;

      //! Get the number of from_Log ports
      //!
      //! \return The number of from_Log ports
      //!
      NATIVE_INT_TYPE getNum_from_Log(void) const;

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Get the number of from_LogText ports
      //!
      //! \return The number of from_LogText ports
      //!
      NATIVE_INT_TYPE getNum_from_LogText(void) const;
#endif

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_Schedin[portNum] is connected
      //!
      bool isConnected_to_Schedin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_PingIn[portNum] is connected
      //!
      bool isConnected_to_PingIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_CmdDisp[portNum] is connected
      //!
      bool isConnected_to_CmdDisp(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      // ----------------------------------------------------------------------
      // Functions for sending commands
      // ----------------------------------------------------------------------

    protected:

      // send command buffers directly - used for intentional command encoding errors
      void sendRawCmd(FwOpcodeType opcode, U32 cmdSeq, Fw::CmdArgBuffer& args);

      //! Send a MS_GET_TM command
      //!
      void sendCmd_MS_GET_TM(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Command response handling
      // ----------------------------------------------------------------------

      //! Handle a command response
      //!
      virtual void cmdResponseIn(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
      );

      //! A type representing a command response
      //!
      typedef struct {
        FwOpcodeType opCode;
        U32 cmdSeq;
        Fw::CommandResponse response;
      } CmdResponse;

      //! The command response history
      //!
      History<CmdResponse> *cmdResponseHistory;

    protected:

      // ----------------------------------------------------------------------
      // Event dispatch
      // ----------------------------------------------------------------------

      //! Dispatch an event
      //!
      void dispatchEvents(
          const FwEventIdType id, /*!< The event ID*/
          Fw::Time& timeTag, /*!< The time*/
          const Fw::LogSeverity severity, /*!< The severity*/
          Fw::LogBuffer& args /*!< The serialized arguments*/
      );

      //! Clear event history
      //!
      void clearEvents(void);

      //! The total number of events seen
      //!
      U32 eventsSize;

#if FW_ENABLE_TEXT_LOGGING

    protected:

      // ----------------------------------------------------------------------
      // Text events
      // ----------------------------------------------------------------------

      //! Handle a text event
      //!
      virtual void textLogIn(
          const FwEventIdType id, /*!< The event ID*/
          Fw::Time& timeTag, /*!< The time*/
          const Fw::TextLogSeverity severity, /*!< The severity*/
          const Fw::TextLogString& text /*!< The event string*/
      );

      //! A history entry for the text log
      //!
      typedef struct {
        U32 id;
        Fw::Time timeTag;
        Fw::TextLogSeverity severity;
        Fw::TextLogString text;
      } TextLogEntry;

      //! The history of text log events
      //!
      History<TextLogEntry> *textLogHistory;

      //! Print a text log history entry
      //!
      static void printTextLogHistoryEntry(
          const TextLogEntry& e,
          FILE* file
      );

      //! Print the text log history
      //!
      void printTextLogHistory(FILE *const file);

#endif

    protected:

      // ----------------------------------------------------------------------
      // Event: MS_DATA
      // ----------------------------------------------------------------------

      //! Handle event MS_DATA
      //!
      virtual void logIn_ACTIVITY_LO_MS_DATA(
          void
      );

      //! Size of history for event MS_DATA
      //!
      U32 eventsSize_MS_DATA;

    protected:

      // ----------------------------------------------------------------------
      // Event: MS_ERROR
      // ----------------------------------------------------------------------

      //! Handle event MS_ERROR
      //!
      virtual void logIn_WARNING_HI_MS_ERROR(
          void
      );

      //! Size of history for event MS_ERROR
      //!
      U32 eventsSize_MS_ERROR;

    protected:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Set the test time for events and telemetry
      //!
      void setTestTime(
          const Fw::Time& timeTag /*!< The time*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to Schedin
      //!
      Svc::OutputSchedPort m_to_Schedin[1];

      //! To port connected to PingIn
      //!
      Svc::OutputPingPort m_to_PingIn[1];

      //! To port connected to CmdDisp
      //!
      Fw::OutputCmdPort m_to_CmdDisp[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to SHT
      //!
      App::InputSHTPortPort m_from_SHT[1];

      //! From port connected to LPS
      //!
      App::InputLPSPortPort m_from_LPS[1];

      //! From port connected to ICM
      //!
      App::InputICMPortPort m_from_ICM[1];

      //! From port connected to PingOut
      //!
      Svc::InputPingPort m_from_PingOut[1];

      //! From port connected to CmdStatus
      //!
      Fw::InputCmdResponsePort m_from_CmdStatus[1];

      //! From port connected to CmdReg
      //!
      Fw::InputCmdRegPort m_from_CmdReg[1];

      //! From port connected to Time
      //!
      Fw::InputTimePort m_from_Time[1];

      //! From port connected to Log
      //!
      Fw::InputLogPort m_from_Log[1];

#if FW_ENABLE_TEXT_LOGGING == 1
      //! From port connected to LogText
      //!
      Fw::InputLogTextPort m_from_LogText[1];
#endif

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_SHT
      //!
      static void from_SHT_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< sht temperature*/
          F32 humidity /*!< sht humidity*/
      );

      //! Static function for port from_LPS
      //!
      static void from_LPS_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< lps temperature*/
          F32 pressure /*!< lps humidity*/
      );

      //! Static function for port from_ICM
      //!
      static void from_ICM_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          App::Angles &angles, 
          App::Vector &gyro, 
          App::Vector &accel, 
          App::Vector &magn 
      );

      //! Static function for port from_PingOut
      //!
      static void from_PingOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Static function for port from_CmdStatus
      //!
      static void from_CmdStatus_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode, /*!< Command Op Code*/
          U32 cmdSeq, /*!< Command Sequence*/
          Fw::CommandResponse response /*!< The command response argument*/
      );

      //! Static function for port from_CmdReg
      //!
      static void from_CmdReg_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode /*!< Command Op Code*/
      );

      //! Static function for port from_Time
      //!
      static void from_Time_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      //! Static function for port from_Log
      //!
      static void from_Log_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::LogSeverity severity, /*!< The severity argument*/
          Fw::LogBuffer &args /*!< Buffer containing serialized log entry*/
      );

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Static function for port from_LogText
      //!
      static void from_LogText_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::TextLogSeverity severity, /*!< The severity argument*/
          Fw::TextLogString &text /*!< Text of log message*/
      );
#endif

    private:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Test time stamp
      //!
      Fw::Time m_testTime;

  };

} // end namespace App

#endif
