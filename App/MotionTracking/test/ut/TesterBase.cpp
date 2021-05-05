// ======================================================================
// \title  MotionTracking/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for MotionTracking component test harness base class
//
// \copyright
// Copyright 2009-2016, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <stdlib.h>
#include <string.h>
#include "TesterBase.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  MotionTrackingTesterBase ::
    MotionTrackingTesterBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
#if FW_OBJECT_NAMES == 1
      Fw::PassiveComponentBase(compName)
#else
      Fw::PassiveComponentBase()
#endif
  {
    // Initialize telemetry histories
    this->tlmHistory_MOTIONTRACKING_ANGLES =
      new History<TlmEntry_MOTIONTRACKING_ANGLES>(maxHistorySize);
    this->tlmHistory_MOTIONTRACKING_GYRO =
      new History<TlmEntry_MOTIONTRACKING_GYRO>(maxHistorySize);
    this->tlmHistory_MOTIONTRACKING_ACCEL =
      new History<TlmEntry_MOTIONTRACKING_ACCEL>(maxHistorySize);
    this->tlmHistory_MOTIONTRACKING_MAGN =
      new History<TlmEntry_MOTIONTRACKING_MAGN>(maxHistorySize);
    // Initialize event histories
#if FW_ENABLE_TEXT_LOGGING
    this->textLogHistory = new History<TextLogEntry>(maxHistorySize);
#endif
    // Initialize histories for typed user output ports
    this->fromPortHistory_PingOut =
      new History<FromPortEntry_PingOut>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  MotionTrackingTesterBase ::
    ~MotionTrackingTesterBase(void)
  {
    // Destroy telemetry histories
    delete this->tlmHistory_MOTIONTRACKING_ANGLES;
    delete this->tlmHistory_MOTIONTRACKING_GYRO;
    delete this->tlmHistory_MOTIONTRACKING_ACCEL;
    delete this->tlmHistory_MOTIONTRACKING_MAGN;
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    // Destroy port histories
    delete this->fromPortHistory_PingOut;
  }

  void MotionTrackingTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port PingOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_PingOut();
        ++_port
    ) {

      this->m_from_PingOut[_port].init();
      this->m_from_PingOut[_port].addCallComp(
          this,
          from_PingOut_static
      );
      this->m_from_PingOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_PingOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_PingOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port Tlm

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_Tlm();
        ++_port
    ) {

      this->m_from_Tlm[_port].init();
      this->m_from_Tlm[_port].addCallComp(
          this,
          from_Tlm_static
      );
      this->m_from_Tlm[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_Tlm[%d]",
          this->m_objName,
          _port
      );
      this->m_from_Tlm[_port].setObjName(_portName);
#endif

    }

    // Attach input port Time

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_Time();
        ++_port
    ) {

      this->m_from_Time[_port].init();
      this->m_from_Time[_port].addCallComp(
          this,
          from_Time_static
      );
      this->m_from_Time[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_Time[%d]",
          this->m_objName,
          _port
      );
      this->m_from_Time[_port].setObjName(_portName);
#endif

    }

    // Attach input port Log

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_Log();
        ++_port
    ) {

      this->m_from_Log[_port].init();
      this->m_from_Log[_port].addCallComp(
          this,
          from_Log_static
      );
      this->m_from_Log[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_Log[%d]",
          this->m_objName,
          _port
      );
      this->m_from_Log[_port].setObjName(_portName);
#endif

    }

    // Attach input port LogText

#if FW_ENABLE_TEXT_LOGGING == 1
    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_LogText();
        ++_port
    ) {

      this->m_from_LogText[_port].init();
      this->m_from_LogText[_port].addCallComp(
          this,
          from_LogText_static
      );
      this->m_from_LogText[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_LogText[%d]",
          this->m_objName,
          _port
      );
      this->m_from_LogText[_port].setObjName(_portName);
#endif

    }
#endif

    // Initialize output port DataIn

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_DataIn();
        ++_port
    ) {
      this->m_to_DataIn[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_DataIn[%d]",
          this->m_objName,
          _port
      );
      this->m_to_DataIn[_port].setObjName(_portName);
#endif

    }

    // Initialize output port PingIn

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_PingIn();
        ++_port
    ) {
      this->m_to_PingIn[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_PingIn[%d]",
          this->m_objName,
          _port
      );
      this->m_to_PingIn[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE MotionTrackingTesterBase ::
    getNum_to_DataIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_DataIn);
  }

  NATIVE_INT_TYPE MotionTrackingTesterBase ::
    getNum_to_PingIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_PingIn);
  }

  NATIVE_INT_TYPE MotionTrackingTesterBase ::
    getNum_from_PingOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_PingOut);
  }

  NATIVE_INT_TYPE MotionTrackingTesterBase ::
    getNum_from_Tlm(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Tlm);
  }

  NATIVE_INT_TYPE MotionTrackingTesterBase ::
    getNum_from_Time(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Time);
  }

  NATIVE_INT_TYPE MotionTrackingTesterBase ::
    getNum_from_Log(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Log);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE MotionTrackingTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    connect_to_DataIn(
        const NATIVE_INT_TYPE portNum,
        App::InputICMPortPort *const DataIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_DataIn(),static_cast<AssertArg>(portNum));
    this->m_to_DataIn[portNum].addCallPort(DataIn);
  }

  void MotionTrackingTesterBase ::
    connect_to_PingIn(
        const NATIVE_INT_TYPE portNum,
        Svc::InputPingPort *const PingIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_PingIn(),static_cast<AssertArg>(portNum));
    this->m_to_PingIn[portNum].addCallPort(PingIn);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    invoke_to_DataIn(
        const NATIVE_INT_TYPE portNum,
        App::Angles &angles,
        App::Vector &gyro,
        App::Vector &accel,
        App::Vector &magn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_DataIn(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_DataIn(),static_cast<AssertArg>(portNum));
    this->m_to_DataIn[portNum].invoke(
        angles, gyro, accel, magn
    );
  }

  void MotionTrackingTesterBase ::
    invoke_to_PingIn(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(portNum < this->getNum_to_PingIn(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_PingIn(),static_cast<AssertArg>(portNum));
    this->m_to_PingIn[portNum].invoke(
        key
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool MotionTrackingTesterBase ::
    isConnected_to_DataIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_DataIn(), static_cast<AssertArg>(portNum));
    return this->m_to_DataIn[portNum].isConnected();
  }

  bool MotionTrackingTesterBase ::
    isConnected_to_PingIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_PingIn(), static_cast<AssertArg>(portNum));
    return this->m_to_PingIn[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Svc::InputPingPort *MotionTrackingTesterBase ::
    get_from_PingOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PingOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_PingOut[portNum];
  }

  Fw::InputTlmPort *MotionTrackingTesterBase ::
    get_from_Tlm(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Tlm(),static_cast<AssertArg>(portNum));
    return &this->m_from_Tlm[portNum];
  }

  Fw::InputTimePort *MotionTrackingTesterBase ::
    get_from_Time(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Time(),static_cast<AssertArg>(portNum));
    return &this->m_from_Time[portNum];
  }

  Fw::InputLogPort *MotionTrackingTesterBase ::
    get_from_Log(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Log(),static_cast<AssertArg>(portNum));
    return &this->m_from_Log[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *MotionTrackingTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    from_PingOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(callComp);
    MotionTrackingTesterBase* _testerBase =
      static_cast<MotionTrackingTesterBase*>(callComp);
    _testerBase->from_PingOut_handlerBase(
        portNum,
        key
    );
  }

  void MotionTrackingTesterBase ::
    from_Tlm_static(
        Fw::PassiveComponentBase *const component,
        NATIVE_INT_TYPE portNum,
        FwChanIdType id,
        Fw::Time &timeTag,
        Fw::TlmBuffer &val
    )
  {
    MotionTrackingTesterBase* _testerBase =
      static_cast<MotionTrackingTesterBase*>(component);
    _testerBase->dispatchTlm(id, timeTag, val);
  }

  void MotionTrackingTesterBase ::
    from_Log_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    MotionTrackingTesterBase* _testerBase =
      static_cast<MotionTrackingTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void MotionTrackingTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    MotionTrackingTesterBase* _testerBase =
      static_cast<MotionTrackingTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void MotionTrackingTesterBase ::
    from_Time_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    MotionTrackingTesterBase* _testerBase =
      static_cast<MotionTrackingTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_PingOut->clear();
  }

  // ----------------------------------------------------------------------
  // From port: PingOut
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    pushFromPortEntry_PingOut(
        U32 key
    )
  {
    FromPortEntry_PingOut _e = {
      key
    };
    this->fromPortHistory_PingOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    from_PingOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(portNum < this->getNum_from_PingOut(),static_cast<AssertArg>(portNum));
    this->from_PingOut_handler(
        portNum,
        key
    );
  }

  // ----------------------------------------------------------------------
  // History
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    clearHistory()
  {
    this->clearTlm();
    this->textLogHistory->clear();
    this->clearEvents();
    this->clearFromPortHistory();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Telemetry dispatch
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    dispatchTlm(
        const FwChanIdType id,
        const Fw::Time &timeTag,
        Fw::TlmBuffer &val
    )
  {

    val.resetDeser();

    const U32 idBase = this->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);

    switch (id - idBase) {

      case MotionTrackingComponentBase::CHANNELID_MOTIONTRACKING_ANGLES:
      {
        App::AnglesTlm arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing MOTIONTRACKING_ANGLES: %d\n", _status);
          return;
        }
        this->tlmInput_MOTIONTRACKING_ANGLES(timeTag, arg);
        break;
      }

      case MotionTrackingComponentBase::CHANNELID_MOTIONTRACKING_GYRO:
      {
        App::VectorTlm arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing MOTIONTRACKING_GYRO: %d\n", _status);
          return;
        }
        this->tlmInput_MOTIONTRACKING_GYRO(timeTag, arg);
        break;
      }

      case MotionTrackingComponentBase::CHANNELID_MOTIONTRACKING_ACCEL:
      {
        App::VectorTlm arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing MOTIONTRACKING_ACCEL: %d\n", _status);
          return;
        }
        this->tlmInput_MOTIONTRACKING_ACCEL(timeTag, arg);
        break;
      }

      case MotionTrackingComponentBase::CHANNELID_MOTIONTRACKING_MAGN:
      {
        App::VectorTlm arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing MOTIONTRACKING_MAGN: %d\n", _status);
          return;
        }
        this->tlmInput_MOTIONTRACKING_MAGN(timeTag, arg);
        break;
      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void MotionTrackingTesterBase ::
    clearTlm(void)
  {
    this->tlmSize = 0;
    this->tlmHistory_MOTIONTRACKING_ANGLES->clear();
    this->tlmHistory_MOTIONTRACKING_GYRO->clear();
    this->tlmHistory_MOTIONTRACKING_ACCEL->clear();
    this->tlmHistory_MOTIONTRACKING_MAGN->clear();
  }

  // ----------------------------------------------------------------------
  // Channel: MOTIONTRACKING_ANGLES
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    tlmInput_MOTIONTRACKING_ANGLES(
        const Fw::Time& timeTag,
        const App::AnglesTlm& val
    )
  {
    TlmEntry_MOTIONTRACKING_ANGLES e = { timeTag, val };
    this->tlmHistory_MOTIONTRACKING_ANGLES->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: MOTIONTRACKING_GYRO
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    tlmInput_MOTIONTRACKING_GYRO(
        const Fw::Time& timeTag,
        const App::VectorTlm& val
    )
  {
    TlmEntry_MOTIONTRACKING_GYRO e = { timeTag, val };
    this->tlmHistory_MOTIONTRACKING_GYRO->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: MOTIONTRACKING_ACCEL
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    tlmInput_MOTIONTRACKING_ACCEL(
        const Fw::Time& timeTag,
        const App::VectorTlm& val
    )
  {
    TlmEntry_MOTIONTRACKING_ACCEL e = { timeTag, val };
    this->tlmHistory_MOTIONTRACKING_ACCEL->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: MOTIONTRACKING_MAGN
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    tlmInput_MOTIONTRACKING_MAGN(
        const Fw::Time& timeTag,
        const App::VectorTlm& val
    )
  {
    TlmEntry_MOTIONTRACKING_MAGN e = { timeTag, val };
    this->tlmHistory_MOTIONTRACKING_MAGN->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    dispatchEvents(
        const FwEventIdType id,
        Fw::Time &timeTag,
        const Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {

    args.resetDeser();

    const U32 idBase = this->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);
    switch (id - idBase) {

      case MotionTrackingComponentBase::EVENTID_MS_DATA:
      {

#if FW_AMPCS_COMPATIBLE
        // For AMPCS, decode zero arguments
        Fw::SerializeStatus _zero_status = Fw::FW_SERIALIZE_OK;
        U8 _noArgs;
        _zero_status = args.deserialize(_noArgs);
        FW_ASSERT(
            _zero_status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_zero_status)
        );
#endif
        this->logIn_ACTIVITY_LO_MS_DATA();

        break;

      }

      case MotionTrackingComponentBase::EVENTID_MS_ERROR:
      {

#if FW_AMPCS_COMPATIBLE
        // For AMPCS, decode zero arguments
        Fw::SerializeStatus _zero_status = Fw::FW_SERIALIZE_OK;
        U8 _noArgs;
        _zero_status = args.deserialize(_noArgs);
        FW_ASSERT(
            _zero_status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_zero_status)
        );
#endif
        this->logIn_WARNING_HI_MS_ERROR();

        break;

      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void MotionTrackingTesterBase ::
    clearEvents(void)
  {
    this->eventsSize = 0;
    this->eventsSize_MS_DATA = 0;
    this->eventsSize_MS_ERROR = 0;
  }

#if FW_ENABLE_TEXT_LOGGING

  // ----------------------------------------------------------------------
  // Text events
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    textLogIn(
        const U32 id,
        Fw::Time &timeTag,
        const Fw::TextLogSeverity severity,
        const Fw::TextLogString &text
    )
  {
    TextLogEntry e = { id, timeTag, severity, text };
    textLogHistory->push_back(e);
  }

  void MotionTrackingTesterBase ::
    printTextLogHistoryEntry(
        const TextLogEntry& e,
        FILE* file
    )
  {
    const char *severityString = "UNKNOWN";
    switch (e.severity) {
      case Fw::TEXT_LOG_FATAL:
        severityString = "FATAL";
        break;
      case Fw::TEXT_LOG_WARNING_HI:
        severityString = "WARNING_HI";
        break;
      case Fw::TEXT_LOG_WARNING_LO:
        severityString = "WARNING_LO";
        break;
      case Fw::TEXT_LOG_COMMAND:
        severityString = "COMMAND";
        break;
      case Fw::TEXT_LOG_ACTIVITY_HI:
        severityString = "ACTIVITY_HI";
        break;
      case Fw::TEXT_LOG_ACTIVITY_LO:
        severityString = "ACTIVITY_LO";
        break;
      case Fw::TEXT_LOG_DIAGNOSTIC:
       severityString = "DIAGNOSTIC";
        break;
      default:
        severityString = "SEVERITY ERROR";
        break;
    }

    fprintf(
        file,
        "EVENT: (%d) (%d:%d,%d) %s: %s\n",
        e.id,
        const_cast<TextLogEntry&>(e).timeTag.getTimeBase(),
        const_cast<TextLogEntry&>(e).timeTag.getSeconds(),
        const_cast<TextLogEntry&>(e).timeTag.getUSeconds(),
        severityString,
        e.text.toChar()
    );

  }

  void MotionTrackingTesterBase ::
    printTextLogHistory(FILE *file)
  {
    for (U32 i = 0; i < this->textLogHistory->size(); ++i) {
      this->printTextLogHistoryEntry(
          this->textLogHistory->at(i),
          file
      );
    }
  }

#endif

  // ----------------------------------------------------------------------
  // Event: MS_DATA
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    logIn_ACTIVITY_LO_MS_DATA(
        void
    )
  {
    ++this->eventsSize_MS_DATA;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: MS_ERROR
  // ----------------------------------------------------------------------

  void MotionTrackingTesterBase ::
    logIn_WARNING_HI_MS_ERROR(
        void
    )
  {
    ++this->eventsSize_MS_ERROR;
    ++this->eventsSize;
  }

} // end namespace App
