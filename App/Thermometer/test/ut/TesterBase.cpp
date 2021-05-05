// ======================================================================
// \title  Thermometer/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for Thermometer component test harness base class
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

  ThermometerTesterBase ::
    ThermometerTesterBase(
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
    this->tlmHistory_THERMOMETER_TEMP =
      new History<TlmEntry_THERMOMETER_TEMP>(maxHistorySize);
    this->tlmHistory_THERMOMETER_HUMI =
      new History<TlmEntry_THERMOMETER_HUMI>(maxHistorySize);
    // Initialize event histories
#if FW_ENABLE_TEXT_LOGGING
    this->textLogHistory = new History<TextLogEntry>(maxHistorySize);
#endif
    this->eventHistory_MS_DATA =
      new History<EventEntry_MS_DATA>(maxHistorySize);
    // Initialize histories for typed user output ports
    this->fromPortHistory_PingOut =
      new History<FromPortEntry_PingOut>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  ThermometerTesterBase ::
    ~ThermometerTesterBase(void)
  {
    // Destroy telemetry histories
    delete this->tlmHistory_THERMOMETER_TEMP;
    delete this->tlmHistory_THERMOMETER_HUMI;
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    delete this->eventHistory_MS_DATA;
    // Destroy port histories
    delete this->fromPortHistory_PingOut;
  }

  void ThermometerTesterBase ::
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

  NATIVE_INT_TYPE ThermometerTesterBase ::
    getNum_to_DataIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_DataIn);
  }

  NATIVE_INT_TYPE ThermometerTesterBase ::
    getNum_to_PingIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_PingIn);
  }

  NATIVE_INT_TYPE ThermometerTesterBase ::
    getNum_from_PingOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_PingOut);
  }

  NATIVE_INT_TYPE ThermometerTesterBase ::
    getNum_from_Tlm(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Tlm);
  }

  NATIVE_INT_TYPE ThermometerTesterBase ::
    getNum_from_Time(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Time);
  }

  NATIVE_INT_TYPE ThermometerTesterBase ::
    getNum_from_Log(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Log);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE ThermometerTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
    connect_to_DataIn(
        const NATIVE_INT_TYPE portNum,
        App::InputSHTPortPort *const DataIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_DataIn(),static_cast<AssertArg>(portNum));
    this->m_to_DataIn[portNum].addCallPort(DataIn);
  }

  void ThermometerTesterBase ::
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

  void ThermometerTesterBase ::
    invoke_to_DataIn(
        const NATIVE_INT_TYPE portNum,
        F32 temperature,
        F32 humidity
    )
  {
    FW_ASSERT(portNum < this->getNum_to_DataIn(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_DataIn(),static_cast<AssertArg>(portNum));
    this->m_to_DataIn[portNum].invoke(
        temperature, humidity
    );
  }

  void ThermometerTesterBase ::
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

  bool ThermometerTesterBase ::
    isConnected_to_DataIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_DataIn(), static_cast<AssertArg>(portNum));
    return this->m_to_DataIn[portNum].isConnected();
  }

  bool ThermometerTesterBase ::
    isConnected_to_PingIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_PingIn(), static_cast<AssertArg>(portNum));
    return this->m_to_PingIn[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Svc::InputPingPort *ThermometerTesterBase ::
    get_from_PingOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PingOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_PingOut[portNum];
  }

  Fw::InputTlmPort *ThermometerTesterBase ::
    get_from_Tlm(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Tlm(),static_cast<AssertArg>(portNum));
    return &this->m_from_Tlm[portNum];
  }

  Fw::InputTimePort *ThermometerTesterBase ::
    get_from_Time(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Time(),static_cast<AssertArg>(portNum));
    return &this->m_from_Time[portNum];
  }

  Fw::InputLogPort *ThermometerTesterBase ::
    get_from_Log(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Log(),static_cast<AssertArg>(portNum));
    return &this->m_from_Log[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *ThermometerTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
    from_PingOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(callComp);
    ThermometerTesterBase* _testerBase =
      static_cast<ThermometerTesterBase*>(callComp);
    _testerBase->from_PingOut_handlerBase(
        portNum,
        key
    );
  }

  void ThermometerTesterBase ::
    from_Tlm_static(
        Fw::PassiveComponentBase *const component,
        NATIVE_INT_TYPE portNum,
        FwChanIdType id,
        Fw::Time &timeTag,
        Fw::TlmBuffer &val
    )
  {
    ThermometerTesterBase* _testerBase =
      static_cast<ThermometerTesterBase*>(component);
    _testerBase->dispatchTlm(id, timeTag, val);
  }

  void ThermometerTesterBase ::
    from_Log_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    ThermometerTesterBase* _testerBase =
      static_cast<ThermometerTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void ThermometerTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    ThermometerTesterBase* _testerBase =
      static_cast<ThermometerTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void ThermometerTesterBase ::
    from_Time_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    ThermometerTesterBase* _testerBase =
      static_cast<ThermometerTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_PingOut->clear();
  }

  // ----------------------------------------------------------------------
  // From port: PingOut
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
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

  void ThermometerTesterBase ::
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

  void ThermometerTesterBase ::
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

  void ThermometerTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Telemetry dispatch
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
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

      case ThermometerComponentBase::CHANNELID_THERMOMETER_TEMP:
      {
        F32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing THERMOMETER_TEMP: %d\n", _status);
          return;
        }
        this->tlmInput_THERMOMETER_TEMP(timeTag, arg);
        break;
      }

      case ThermometerComponentBase::CHANNELID_THERMOMETER_HUMI:
      {
        F32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing THERMOMETER_HUMI: %d\n", _status);
          return;
        }
        this->tlmInput_THERMOMETER_HUMI(timeTag, arg);
        break;
      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void ThermometerTesterBase ::
    clearTlm(void)
  {
    this->tlmSize = 0;
    this->tlmHistory_THERMOMETER_TEMP->clear();
    this->tlmHistory_THERMOMETER_HUMI->clear();
  }

  // ----------------------------------------------------------------------
  // Channel: THERMOMETER_TEMP
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
    tlmInput_THERMOMETER_TEMP(
        const Fw::Time& timeTag,
        const F32& val
    )
  {
    TlmEntry_THERMOMETER_TEMP e = { timeTag, val };
    this->tlmHistory_THERMOMETER_TEMP->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: THERMOMETER_HUMI
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
    tlmInput_THERMOMETER_HUMI(
        const Fw::Time& timeTag,
        const F32& val
    )
  {
    TlmEntry_THERMOMETER_HUMI e = { timeTag, val };
    this->tlmHistory_THERMOMETER_HUMI->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
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

      case ThermometerComponentBase::EVENTID_MS_DATA:
      {

        Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;
#if FW_AMPCS_COMPATIBLE
        // Deserialize the number of arguments.
        U8 _numArgs;
        _status = args.deserialize(_numArgs);
        FW_ASSERT(
          _status == Fw::FW_SERIALIZE_OK,
          static_cast<AssertArg>(_status)
        );
        // verify they match expected.
        FW_ASSERT(_numArgs == 2,_numArgs,2);

#endif
        F32 temp;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(F32),_argSize,sizeof(F32));
        }
#endif
        _status = args.deserialize(temp);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        F32 humi;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(F32),_argSize,sizeof(F32));
        }
#endif
        _status = args.deserialize(humi);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_LO_MS_DATA(temp, humi);

        break;

      }

      case ThermometerComponentBase::EVENTID_MS_ERROR:
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

  void ThermometerTesterBase ::
    clearEvents(void)
  {
    this->eventsSize = 0;
    this->eventHistory_MS_DATA->clear();
    this->eventsSize_MS_ERROR = 0;
  }

#if FW_ENABLE_TEXT_LOGGING

  // ----------------------------------------------------------------------
  // Text events
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
    textLogIn(
        const FwEventIdType id,
        Fw::Time &timeTag,
        const Fw::TextLogSeverity severity,
        const Fw::TextLogString &text
    )
  {
    TextLogEntry e = { id, timeTag, severity, text };
    textLogHistory->push_back(e);
  }

  void ThermometerTesterBase ::
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

  void ThermometerTesterBase ::
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

  void ThermometerTesterBase ::
    logIn_ACTIVITY_LO_MS_DATA(
        F32 temp,
        F32 humi
    )
  {
    EventEntry_MS_DATA e = {
      temp, humi
    };
    eventHistory_MS_DATA->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: MS_ERROR
  // ----------------------------------------------------------------------

  void ThermometerTesterBase ::
    logIn_WARNING_HI_MS_ERROR(
        void
    )
  {
    ++this->eventsSize_MS_ERROR;
    ++this->eventsSize;
  }

} // end namespace App
