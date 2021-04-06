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
    // Initialize histories for typed user output ports
    this->fromPortHistory_SHTTemperature =
      new History<FromPortEntry_SHTTemperature>(maxHistorySize);
    this->fromPortHistory_SHTHumidity =
      new History<FromPortEntry_SHTHumidity>(maxHistorySize);
    this->fromPortHistory_PingOut =
      new History<FromPortEntry_PingOut>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  SenseHatTesterBase ::
    ~SenseHatTesterBase(void)
  {
    // Destroy port histories
    delete this->fromPortHistory_SHTTemperature;
    // Destroy port histories
    delete this->fromPortHistory_SHTHumidity;
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

    // Attach input port SHTTemperature

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_SHTTemperature();
        ++_port
    ) {

      this->m_from_SHTTemperature[_port].init();
      this->m_from_SHTTemperature[_port].addCallComp(
          this,
          from_SHTTemperature_static
      );
      this->m_from_SHTTemperature[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_SHTTemperature[%d]",
          this->m_objName,
          _port
      );
      this->m_from_SHTTemperature[_port].setObjName(_portName);
#endif

    }

    // Attach input port SHTHumidity

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_SHTHumidity();
        ++_port
    ) {

      this->m_from_SHTHumidity[_port].init();
      this->m_from_SHTHumidity[_port].addCallComp(
          this,
          from_SHTHumidity_static
      );
      this->m_from_SHTHumidity[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_SHTHumidity[%d]",
          this->m_objName,
          _port
      );
      this->m_from_SHTHumidity[_port].setObjName(_portName);
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
    getNum_from_SHTTemperature(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_SHTTemperature);
  }

  NATIVE_INT_TYPE SenseHatTesterBase ::
    getNum_from_SHTHumidity(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_SHTHumidity);
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

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  App::InputSenseHatFloatDataPort *SenseHatTesterBase ::
    get_from_SHTTemperature(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_SHTTemperature(),static_cast<AssertArg>(portNum));
    return &this->m_from_SHTTemperature[portNum];
  }

  App::InputSenseHatFloatDataPort *SenseHatTesterBase ::
    get_from_SHTHumidity(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_SHTHumidity(),static_cast<AssertArg>(portNum));
    return &this->m_from_SHTHumidity[portNum];
  }

  Svc::InputPingPort *SenseHatTesterBase ::
    get_from_PingOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PingOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_PingOut[portNum];
  }

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    from_SHTTemperature_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    FW_ASSERT(callComp);
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(callComp);
    _testerBase->from_SHTTemperature_handlerBase(
        portNum,
        result
    );
  }

  void SenseHatTesterBase ::
    from_SHTHumidity_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    FW_ASSERT(callComp);
    SenseHatTesterBase* _testerBase =
      static_cast<SenseHatTesterBase*>(callComp);
    _testerBase->from_SHTHumidity_handlerBase(
        portNum,
        result
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

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_SHTTemperature->clear();
    this->fromPortHistory_SHTHumidity->clear();
    this->fromPortHistory_PingOut->clear();
  }

  // ----------------------------------------------------------------------
  // From port: SHTTemperature
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    pushFromPortEntry_SHTTemperature(
        F32 result
    )
  {
    FromPortEntry_SHTTemperature _e = {
      result
    };
    this->fromPortHistory_SHTTemperature->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: SHTHumidity
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    pushFromPortEntry_SHTHumidity(
        F32 result
    )
  {
    FromPortEntry_SHTHumidity _e = {
      result
    };
    this->fromPortHistory_SHTHumidity->push_back(_e);
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
    from_SHTTemperature_handlerBase(
        const NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    FW_ASSERT(portNum < this->getNum_from_SHTTemperature(),static_cast<AssertArg>(portNum));
    this->from_SHTTemperature_handler(
        portNum,
        result
    );
  }

  void SenseHatTesterBase ::
    from_SHTHumidity_handlerBase(
        const NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    FW_ASSERT(portNum < this->getNum_from_SHTHumidity(),static_cast<AssertArg>(portNum));
    this->from_SHTHumidity_handler(
        portNum,
        result
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
  // History
  // ----------------------------------------------------------------------

  void SenseHatTesterBase ::
    clearHistory()
  {
    this->clearFromPortHistory();
  }

} // end namespace App
