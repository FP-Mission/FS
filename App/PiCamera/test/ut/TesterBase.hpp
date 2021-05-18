// ======================================================================
// \title  PiCamera/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for PiCamera component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef PiCamera_TESTER_BASE_HPP
#define PiCamera_TESTER_BASE_HPP

#include <App/PiCamera/PiCameraComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace App {

  //! \class PiCameraTesterBase
  //! \brief Auto-generated base class for PiCamera component test harness
  //!
  class PiCameraTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object PiCameraTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect PingIn to to_PingIn[portNum]
      //!
      void connect_to_PingIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputPingPort *const PingIn /*!< The port*/
      );

      //! Connect position to to_position[portNum]
      //!
      void connect_to_position(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          App::InputPositionPort *const position /*!< The port*/
      );

      //! Connect barometerDataIn to to_barometerDataIn[portNum]
      //!
      void connect_to_barometerDataIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          App::InputPiCameraBarometerPortPort *const barometerDataIn /*!< The port*/
      );

      //! Connect SizeIn to to_SizeIn[portNum]
      //!
      void connect_to_SizeIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          App::InputPiCameraSizePortPort *const SizeIn /*!< The port*/
      );

      //! Connect Schedin to to_Schedin[portNum]
      //!
      void connect_to_Schedin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputSchedPort *const Schedin /*!< The port*/
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

      //! Get the port that receives input from PingOut
      //!
      //! \return from_PingOut[portNum]
      //!
      Svc::InputPingPort* get_from_PingOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from PictureOut
      //!
      //! \return from_PictureOut[portNum]
      //!
      App::InputPiCameraPicturePortPort* get_from_PictureOut(
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

      //! Get the port that receives input from Tlm
      //!
      //! \return from_Tlm[portNum]
      //!
      Fw::InputTlmPort* get_from_Tlm(
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

      //! Construct object PiCameraTesterBase
      //!
      PiCameraTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object PiCameraTesterBase
      //!
      virtual ~PiCameraTesterBase(void);

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

      //! Handler prototype for from_PictureOut
      //!
      virtual void from_PictureOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 path /*!< path of picture*/
      ) = 0;

      //! Handler base function for from_PictureOut
      //!
      void from_PictureOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 path /*!< path of picture*/
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

      //! Push an entry on the history for from_PictureOut
      void pushFromPortEntry_PictureOut(
          U32 path /*!< path of picture*/
      );

      //! A history entry for from_PictureOut
      //!
      typedef struct {
          U32 path;
      } FromPortEntry_PictureOut;

      //! The history for from_PictureOut
      //!
      History<FromPortEntry_PictureOut>
        *fromPortHistory_PictureOut;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to PingIn
      //!
      void invoke_to_PingIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Invoke the to port connected to position
      //!
      void invoke_to_position(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time time, /*!< Measure time*/
          F64 latitude, /*!< Latitude in ? @todo*/
          F64 longitude, /*!< Longitude in ? @todo*/
          U16 altitude, /*!< Altitude in meters*/
          U8 satellite /*!< Satellite count*/
      );

      //! Invoke the to port connected to barometerDataIn
      //!
      void invoke_to_barometerDataIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U16 altitude, /*!< Altitude value*/
          F32 pressure, /*!< Pressure value*/
          F32 temperature /*!< Temperature value*/
      );

      //! Invoke the to port connected to SizeIn
      //!
      void invoke_to_SizeIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 width, /*!< width value*/
          U32 height /*!< height value*/
      );

      //! Invoke the to port connected to Schedin
      //!
      void invoke_to_Schedin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

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

      //! Get the number of to_position ports
      //!
      //! \return The number of to_position ports
      //!
      NATIVE_INT_TYPE getNum_to_position(void) const;

      //! Get the number of to_barometerDataIn ports
      //!
      //! \return The number of to_barometerDataIn ports
      //!
      NATIVE_INT_TYPE getNum_to_barometerDataIn(void) const;

      //! Get the number of to_SizeIn ports
      //!
      //! \return The number of to_SizeIn ports
      //!
      NATIVE_INT_TYPE getNum_to_SizeIn(void) const;

      //! Get the number of to_Schedin ports
      //!
      //! \return The number of to_Schedin ports
      //!
      NATIVE_INT_TYPE getNum_to_Schedin(void) const;

      //! Get the number of from_PictureOut ports
      //!
      //! \return The number of from_PictureOut ports
      //!
      NATIVE_INT_TYPE getNum_from_PictureOut(void) const;

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

      //! Get the number of from_Tlm ports
      //!
      //! \return The number of from_Tlm ports
      //!
      NATIVE_INT_TYPE getNum_from_Tlm(void) const;

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
      //! Whether to_PingIn[portNum] is connected
      //!
      bool isConnected_to_PingIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_position[portNum] is connected
      //!
      bool isConnected_to_position(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_barometerDataIn[portNum] is connected
      //!
      bool isConnected_to_barometerDataIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_SizeIn[portNum] is connected
      //!
      bool isConnected_to_SizeIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_Schedin[portNum] is connected
      //!
      bool isConnected_to_Schedin(
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

      //! Send a PiCam_TakePicture command
      //!
      void sendCmd_PiCam_TakePicture(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Send a PiCam_SetSize command
      //!
      void sendCmd_PiCam_SetSize(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 width, /*!< Image Width*/
          U32 height /*!< Image Height*/
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
      // Event: PiCam_PictureTaken
      // ----------------------------------------------------------------------

      //! Handle event PiCam_PictureTaken
      //!
      virtual void logIn_ACTIVITY_LO_PiCam_PictureTaken(
          void
      );

      //! Size of history for event PiCam_PictureTaken
      //!
      U32 eventsSize_PiCam_PictureTaken;

    protected:

      // ----------------------------------------------------------------------
      // Event: PiCam_PositionUpdate
      // ----------------------------------------------------------------------

      //! Handle event PiCam_PositionUpdate
      //!
      virtual void logIn_ACTIVITY_LO_PiCam_PositionUpdate(
          void
      );

      //! Size of history for event PiCam_PositionUpdate
      //!
      U32 eventsSize_PiCam_PositionUpdate;

    protected:

      // ----------------------------------------------------------------------
      // Event: PiCam_BarometerDataUpdate
      // ----------------------------------------------------------------------

      //! Handle event PiCam_BarometerDataUpdate
      //!
      virtual void logIn_ACTIVITY_LO_PiCam_BarometerDataUpdate(
          F32 temp, /*!< temp*/
          F32 pressure, /*!< temp*/
          U16 altitude /*!< temp*/
      );

      //! A history entry for event PiCam_BarometerDataUpdate
      //!
      typedef struct {
        F32 temp;
        F32 pressure;
        U16 altitude;
      } EventEntry_PiCam_BarometerDataUpdate;

      //! The history of PiCam_BarometerDataUpdate events
      //!
      History<EventEntry_PiCam_BarometerDataUpdate>
        *eventHistory_PiCam_BarometerDataUpdate;

    protected:

      // ----------------------------------------------------------------------
      // Event: PiCam_PictureError
      // ----------------------------------------------------------------------

      //! Handle event PiCam_PictureError
      //!
      virtual void logIn_WARNING_LO_PiCam_PictureError(
          U32 code /*!< Error code*/
      );

      //! A history entry for event PiCam_PictureError
      //!
      typedef struct {
        U32 code;
      } EventEntry_PiCam_PictureError;

      //! The history of PiCam_PictureError events
      //!
      History<EventEntry_PiCam_PictureError>
        *eventHistory_PiCam_PictureError;

    protected:

      // ----------------------------------------------------------------------
      // Telemetry dispatch
      // ----------------------------------------------------------------------

      //! Dispatch telemetry
      //!
      void dispatchTlm(
          const FwChanIdType id, /*!< The channel ID*/
          const Fw::Time& timeTag, /*!< The time*/
          Fw::TlmBuffer& val /*!< The channel value*/
      );

      //! Clear telemetry history
      //!
      void clearTlm(void);

      //! The total number of telemetry inputs seen
      //!
      U32 tlmSize;

    protected:

      // ----------------------------------------------------------------------
      // Channel: PiCam_PictureCnt
      // ----------------------------------------------------------------------

      //! Handle channel PiCam_PictureCnt
      //!
      virtual void tlmInput_PiCam_PictureCnt(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel PiCam_PictureCnt
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_PiCam_PictureCnt;

      //! The history of PiCam_PictureCnt values
      //!
      History<TlmEntry_PiCam_PictureCnt>
        *tlmHistory_PiCam_PictureCnt;

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

      //! To port connected to PingIn
      //!
      Svc::OutputPingPort m_to_PingIn[1];

      //! To port connected to position
      //!
      App::OutputPositionPort m_to_position[1];

      //! To port connected to barometerDataIn
      //!
      App::OutputPiCameraBarometerPortPort m_to_barometerDataIn[1];

      //! To port connected to SizeIn
      //!
      App::OutputPiCameraSizePortPort m_to_SizeIn[1];

      //! To port connected to Schedin
      //!
      Svc::OutputSchedPort m_to_Schedin[1];

      //! To port connected to CmdDisp
      //!
      Fw::OutputCmdPort m_to_CmdDisp[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to PingOut
      //!
      Svc::InputPingPort m_from_PingOut[1];

      //! From port connected to PictureOut
      //!
      App::InputPiCameraPicturePortPort m_from_PictureOut[1];

      //! From port connected to CmdStatus
      //!
      Fw::InputCmdResponsePort m_from_CmdStatus[1];

      //! From port connected to CmdReg
      //!
      Fw::InputCmdRegPort m_from_CmdReg[1];

      //! From port connected to Tlm
      //!
      Fw::InputTlmPort m_from_Tlm[1];

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

      //! Static function for port from_PingOut
      //!
      static void from_PingOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Static function for port from_PictureOut
      //!
      static void from_PictureOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 path /*!< path of picture*/
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

      //! Static function for port from_Tlm
      //!
      static void from_Tlm_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwChanIdType id, /*!< Telemetry Channel ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::TlmBuffer &val /*!< Buffer containing serialized telemetry value*/
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
