// ======================================================================
// \title  SenseHat/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for SenseHat component test harness base class
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

  SenseHatTesterBase ::
    SenseHatTesterBase(
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
    // Initialize command history
    this->cmdResponseHistory = new History<CmdResponse>(maxHistorySize);
    // Initialize event histories
#if FW_ENABLE_TEXT_LOGGING
    this->textLogHistory = new History<TextLogEntry>(maxHistorySize);
#endif
    // Initialize histories for typed user output ports
    this->fromPortHistory_SHT =
      new History<FromPortEntry_SHT>(maxHistorySize);
    this->fromPortHistory_LPS =
      new History<FromPortEntry_LPS>(maxHistorySize);
    this->fromPortHistory_ICM =
      new History<FromPortEntry_ICM>(maxHistorySize);
    this->fromPortHistory_PingOut =
      new History<FromPortEntry_PingOut>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  SenseHatTesterBase ::
    ~SenseHatTesterBase(void)
  {
    // Destroy command history
    delete this->cmdResponseHistory;
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    // Destroy port histories
    delete this->fromPortHistory_SHT;
    // Destroy port histories
    delete this->fromPortHistory_LPS;
    // Destroy port histories
    delete this->fromPortHistory_ICM;
    // Destroy port histories
    delete this->fromPortHistory_PingOut;
  }

  void SenseHatTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port SHT

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_SHT();
        ++_port
    ) {

      this->m_from_SHT[_port].init();
      this->m_from_SHT[_port].addCallComp(
          this,
          from_SHT_static
      );
      this->m_from_SHT[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_SHT[%d]",
          this->m_objName,
          _port
      );
      this->m_from_SHT[_port].setObjName(_portName);
#endif

    }

    // Attach input port LPS

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_LPS();
        ++_port
    ) {

      this->m_from_LPS[_port].init();
      this->m_from_LPS[_port].addCallComp(
          this,
          from_LPS_static
      );
      this->m_from_LPS[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_LPS[%d]",
          this->m_objName,
          _port
      );
      this->m_from_LPS[_port].setObjName(_portName);
#endif

    }

    // Attach input port ICM

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_ICM();
        ++_port
    ) {

      this->m_from_ICM[_port].init();
      this->m_from_ICM[_port].addCallComp(
          this,
          from_ICM_static
      );
      this->m_from_ICM[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_ICM[%d]",
          this->m_objName,
          _port
      );
      this->m_from_ICM[_port].setObjName(_portName);
#endif

    }

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

    // Attach input port CmdStatus

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_CmdStatus();
        ++_port
    ) {

      this->m_from_CmdStatus[_port].init();
      this->m_from_CmdStatus[_port].addCallComp(
          this,
          from_CmdStatus_static
      );
      this->m_from_CmdStatus[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_CmdStatus[%d]",
          this->m_objName,
          _port
      );
      this->m_from_CmdStatus[_port].setObjName(_portName);
#endif

    }

    // Attach input port CmdReg

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_CmdReg();
        ++_port
    ) {

      this->m_from_CmdReg[_port].init();
      this->m_from_CmdReg[_port].addCallComp(
          this,
          from_CmdReg_static
      );
      this->m_from_CmdReg[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_CmdReg[%d]",
          this->m_objName,
          _port
      );
      this->m_from_CmdReg[_port].setObjName(_portName);
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

    // Initialize output port Schedin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_Schedin();
        ++_port
    ) {
      this->m_to_Schedin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_Schedin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_Schedin[_port].setObjName(_portName);
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

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_SHT(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_SHT);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_LPS(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LPS);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_ICM(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_ICM);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_to_Schedin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_Schedin);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_to_PingIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_PingIn);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_PingOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_PingOut);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_to_CmdDisp(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_CmdDisp);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_CmdStatus(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_CmdStatus);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_CmdReg(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_CmdReg);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_Time(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Time);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_Log(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Log);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    connect_to_Schedin(
        const NATIVE_INT_TYPE portNum,
        Svc::InputSchedPort *const Schedin
    )
  {
    FW_ASSERT(portNum < this->getNum_to_Schedin(),static_cast<AssertArg>(portNum));
    this->m_to_Schedin[portNum].addCallPort(Schedin);
  }

  void SenseHatTesterBase ::
    connect_to_PingIn(
        const NATIVE_INT_TYPE portNum,
        Svc::InputPingPort *const PingIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_PingIn(),static_cast<AssertArg>(portNum));
    this->m_to_PingIn[portNum].addCallPort(PingIn);
  }

  void SenseHatTesterBase ::
    connect_to_CmdDisp(
        const NATIVE_INT_TYPE portNum,
        Fw::InputCmdPort *const CmdDisp
    )
  {
    FW_ASSERT(portNum < this->getNum_to_CmdDisp(),static_cast<AssertArg>(portNum));
    this->m_to_CmdDisp[portNum].addCallPort(CmdDisp);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    invoke_to_Schedin(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(portNum < this->getNum_to_Schedin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_Schedin(),static_cast<AssertArg>(portNum));
    this->m_to_Schedin[portNum].invoke(
        context
    );
  }

  void SenseHatTesterBase ::
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

  bool SenseHatTesterBase ::
    isConnected_to_Schedin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_Schedin(), static_cast<AssertArg>(portNum));
    return this->m_to_Schedin[portNum].isConnected();
  }

  bool SenseHatTesterBase ::
    isConnected_to_PingIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_PingIn(), static_cast<AssertArg>(portNum));
    return this->m_to_PingIn[portNum].isConnected();
  }

  bool SenseHatTesterBase ::
    isConnected_to_CmdDisp(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_CmdDisp(), static_cast<AssertArg>(portNum));
    return this->m_to_CmdDisp[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  App::InputSHTPortPort *SenseHatTesterBase ::
    get_from_SHT(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_SHT(),static_cast<AssertArg>(portNum));
    return &this->m_from_SHT[portNum];
  }

  App::InputLPSPortPort *SenseHatTesterBase ::
    get_from_LPS(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LPS(),static_cast<AssertArg>(portNum));
    return &this->m_from_LPS[portNum];
  }

  App::InputICMPortPort *SenseHatTesterBase ::
    get_from_ICM(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_ICM(),static_cast<AssertArg>(portNum));
    return &this->m_from_ICM[portNum];
  }

  Svc::InputPingPort *SenseHatTesterBase ::
    get_from_PingOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PingOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_PingOut[portNum];
  }

  Fw::InputCmdResponsePort *SenseHatTesterBase ::
    get_from_CmdStatus(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_CmdStatus(),static_cast<AssertArg>(portNum));
    return &this->m_from_CmdStatus[portNum];
  }

  Fw::InputCmdRegPort *SenseHatTesterBase ::
    get_from_CmdReg(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_CmdReg(),static_cast<AssertArg>(portNum));
    return &this->m_from_CmdReg[portNum];
  }

  Fw::InputTimePort *SenseHatTesterBase ::
    get_from_Time(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Time(),static_cast<AssertArg>(portNum));
    return &this->m_from_Time[portNum];
  }

  Fw::InputLogPort *SenseHatTesterBase ::
    get_from_Log(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Log(),static_cast<AssertArg>(portNum));
    return &this->m_from_Log[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *SenseHatTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    from_SHT_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        F32 temperature,
        F32 humidity
    )
  {
    FW_ASSERT(callComp);
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(callComp);
    _testerBase->from_SHT_handlerBase(
        portNum,
        temperature, humidity
    );
  }

  void SenseHatTesterBase ::
    from_LPS_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        F32 temperature,
        F32 pressure
    )
  {
    FW_ASSERT(callComp);
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(callComp);
    _testerBase->from_LPS_handlerBase(
        portNum,
        temperature, pressure
    );
  }

  void SenseHatTesterBase ::
    from_ICM_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        App::Angles &angles,
        App::Vector &gyro,
        App::Vector &accel,
        App::Vector &magn
    )
  {
    FW_ASSERT(callComp);
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(callComp);
    _testerBase->from_ICM_handlerBase(
        portNum,
        angles, gyro, accel, magn
    );
  }

  void SenseHatTesterBase ::
    from_PingOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(callComp);
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(callComp);
    _testerBase->from_PingOut_handlerBase(
        portNum,
        key
    );
  }

  void SenseHatTesterBase ::
    from_CmdStatus_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
  {
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(component);
    _testerBase->cmdResponseIn(opCode, cmdSeq, response);
  }

  void SenseHatTesterBase ::
    from_CmdReg_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode
    )
  {

  }

  void SenseHatTesterBase ::
    from_Log_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void SenseHatTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void SenseHatTesterBase ::
    from_Time_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_SHT->clear();
    this->fromPortHistory_LPS->clear();
    this->fromPortHistory_ICM->clear();
    this->fromPortHistory_PingOut->clear();
  }

  // ----------------------------------------------------------------------
  // From port: SHT
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    pushFromPortEntry_SHT(
        F32 temperature,
        F32 humidity
    )
  {
    FromPortEntry_SHT _e = {
      temperature, humidity
    };
    this->fromPortHistory_SHT->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: LPS
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    pushFromPortEntry_LPS(
        F32 temperature,
        F32 pressure
    )
  {
    FromPortEntry_LPS _e = {
      temperature, pressure
    };
    this->fromPortHistory_LPS->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: ICM
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    pushFromPortEntry_ICM(
        App::Angles &angles,
        App::Vector &gyro,
        App::Vector &accel,
        App::Vector &magn
    )
  {
    FromPortEntry_ICM _e = {
      angles, gyro, accel, magn
    };
    this->fromPortHistory_ICM->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: PingOut
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
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

  void SenseHatTesterBase ::
    from_SHT_handlerBase(
        const NATIVE_INT_TYPE portNum,
        F32 temperature,
        F32 humidity
    )
  {
    FW_ASSERT(portNum < this->getNum_from_SHT(),static_cast<AssertArg>(portNum));
    this->from_SHT_handler(
        portNum,
        temperature, humidity
    );
  }

  void SenseHatTesterBase ::
    from_LPS_handlerBase(
        const NATIVE_INT_TYPE portNum,
        F32 temperature,
        F32 pressure
    )
  {
    FW_ASSERT(portNum < this->getNum_from_LPS(),static_cast<AssertArg>(portNum));
    this->from_LPS_handler(
        portNum,
        temperature, pressure
    );
  }

  void SenseHatTesterBase ::
    from_ICM_handlerBase(
        const NATIVE_INT_TYPE portNum,
        App::Angles &angles,
        App::Vector &gyro,
        App::Vector &accel,
        App::Vector &magn
    )
  {
    FW_ASSERT(portNum < this->getNum_from_ICM(),static_cast<AssertArg>(portNum));
    this->from_ICM_handler(
        portNum,
        angles, gyro, accel, magn
    );
  }

  void SenseHatTesterBase ::
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
  // Command response handling
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    cmdResponseIn(
        const FwOpcodeType opCode,
        const U32 seq,
        const Fw::CommandResponse response
    )
  {
    CmdResponse e = { opCode, seq, response };
    this->cmdResponseHistory->push_back(e);
  }

  // ----------------------------------------------------------------------
  // Command: MS_GET_TM
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    sendCmd_MS_GET_TM(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = SenseHatComponentBase::OPCODE_MS_GET_TM + idBase;

    if (this->m_to_CmdDisp[0].isConnected()) {
      this->m_to_CmdDisp[0].invoke(
          _opcode,
          cmdSeq,
          buff
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }


  void SenseHatTesterBase ::
    sendRawCmd(FwOpcodeType opcode, U32 cmdSeq, Fw::CmdArgBuffer& args) {

    const U32 idBase = this->getIdBase();
    FwOpcodeType _opcode = opcode + idBase;
    if (this->m_to_CmdDisp[0].isConnected()) {
      this->m_to_CmdDisp[0].invoke(
          _opcode,
          cmdSeq,
          args
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }

  // ----------------------------------------------------------------------
  // History
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    clearHistory()
  {
    this->cmdResponseHistory->clear();
    this->textLogHistory->clear();
    this->clearEvents();
    this->clearFromPortHistory();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
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

      case SenseHatComponentBase::EVENTID_MS_DATA:
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

      case SenseHatComponentBase::EVENTID_MS_ERROR:
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

  void SenseHatTesterBase ::
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

  void SenseHatTesterBase ::
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

  void SenseHatTesterBase ::
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

  void SenseHatTesterBase ::
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

  void SenseHatTesterBase ::
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

  void SenseHatTesterBase ::
    logIn_WARNING_HI_MS_ERROR(
        void
    )
  {
    ++this->eventsSize_MS_ERROR;
    ++this->eventsSize;
  }

} // end namespace App
