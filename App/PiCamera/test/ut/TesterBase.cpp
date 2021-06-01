// ======================================================================
// \title  PiCamera/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for PiCamera component test harness base class
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

  PiCameraTesterBase ::
    PiCameraTesterBase(
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
    // Initialize telemetry histories
    this->tlmHistory_PiCam_PictureCnt =
      new History<TlmEntry_PiCam_PictureCnt>(maxHistorySize);
    this->tlmHistory_PiCam_PictureSize =
      new History<TlmEntry_PiCam_PictureSize>(maxHistorySize);
    this->tlmHistory_PiCam_Timeinterval =
      new History<TlmEntry_PiCam_Timeinterval>(maxHistorySize);
    // Initialize event histories
#if FW_ENABLE_TEXT_LOGGING
    this->textLogHistory = new History<TextLogEntry>(maxHistorySize);
#endif
    this->eventHistory_PiCam_BarometerDataUpdate =
      new History<EventEntry_PiCam_BarometerDataUpdate>(maxHistorySize);
    this->eventHistory_PiCam_PictureError =
      new History<EventEntry_PiCam_PictureError>(maxHistorySize);
    this->eventHistory_PiCam_SetTimeInterval =
      new History<EventEntry_PiCam_SetTimeInterval>(maxHistorySize);
    this->eventHistory_PiCam_SetPictureSize =
      new History<EventEntry_PiCam_SetPictureSize>(maxHistorySize);
    // Initialize histories for typed user output ports
    this->fromPortHistory_PingOut =
      new History<FromPortEntry_PingOut>(maxHistorySize);
    this->fromPortHistory_PictureOut =
      new History<FromPortEntry_PictureOut>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  PiCameraTesterBase ::
    ~PiCameraTesterBase(void)
  {
    // Destroy command history
    delete this->cmdResponseHistory;
    // Destroy telemetry histories
    delete this->tlmHistory_PiCam_PictureCnt;
    delete this->tlmHistory_PiCam_PictureSize;
    delete this->tlmHistory_PiCam_Timeinterval;
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    delete this->eventHistory_PiCam_BarometerDataUpdate;
    delete this->eventHistory_PiCam_PictureError;
    delete this->eventHistory_PiCam_SetTimeInterval;
    delete this->eventHistory_PiCam_SetPictureSize;
    // Destroy port histories
    delete this->fromPortHistory_PingOut;
    // Destroy port histories
    delete this->fromPortHistory_PictureOut;
  }

  void PiCameraTesterBase ::
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

    // Attach input port PictureOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_PictureOut();
        ++_port
    ) {

      this->m_from_PictureOut[_port].init();
      this->m_from_PictureOut[_port].addCallComp(
          this,
          from_PictureOut_static
      );
      this->m_from_PictureOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_PictureOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_PictureOut[_port].setObjName(_portName);
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

    // Initialize output port position

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_position();
        ++_port
    ) {
      this->m_to_position[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_position[%d]",
          this->m_objName,
          _port
      );
      this->m_to_position[_port].setObjName(_portName);
#endif

    }

    // Initialize output port barometerDataIn

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_barometerDataIn();
        ++_port
    ) {
      this->m_to_barometerDataIn[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_barometerDataIn[%d]",
          this->m_objName,
          _port
      );
      this->m_to_barometerDataIn[_port].setObjName(_portName);
#endif

    }

    // Initialize output port SizeIn

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_SizeIn();
        ++_port
    ) {
      this->m_to_SizeIn[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_SizeIn[%d]",
          this->m_objName,
          _port
      );
      this->m_to_SizeIn[_port].setObjName(_portName);
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

    // Initialize output port SendFrame

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_SendFrame();
        ++_port
    ) {
      this->m_to_SendFrame[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_SendFrame[%d]",
          this->m_objName,
          _port
      );
      this->m_to_SendFrame[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_to_PingIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_PingIn);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_from_PingOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_PingOut);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_to_position(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_position);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_to_barometerDataIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_barometerDataIn);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_to_SizeIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_SizeIn);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_to_Schedin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_Schedin);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_from_PictureOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_PictureOut);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_to_SendFrame(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_SendFrame);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_to_CmdDisp(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_CmdDisp);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_from_CmdStatus(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_CmdStatus);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_from_CmdReg(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_CmdReg);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_from_Tlm(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Tlm);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_from_Time(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Time);
  }

  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_from_Log(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Log);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE PiCameraTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    connect_to_PingIn(
        const NATIVE_INT_TYPE portNum,
        Svc::InputPingPort *const PingIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_PingIn(),static_cast<AssertArg>(portNum));
    this->m_to_PingIn[portNum].addCallPort(PingIn);
  }

  void PiCameraTesterBase ::
    connect_to_position(
        const NATIVE_INT_TYPE portNum,
        App::InputPositionPort *const position
    )
  {
    FW_ASSERT(portNum < this->getNum_to_position(),static_cast<AssertArg>(portNum));
    this->m_to_position[portNum].addCallPort(position);
  }

  void PiCameraTesterBase ::
    connect_to_barometerDataIn(
        const NATIVE_INT_TYPE portNum,
        App::InputPiCameraBarometerPortPort *const barometerDataIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_barometerDataIn(),static_cast<AssertArg>(portNum));
    this->m_to_barometerDataIn[portNum].addCallPort(barometerDataIn);
  }

  void PiCameraTesterBase ::
    connect_to_SizeIn(
        const NATIVE_INT_TYPE portNum,
        App::InputPiCameraSizePortPort *const SizeIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_SizeIn(),static_cast<AssertArg>(portNum));
    this->m_to_SizeIn[portNum].addCallPort(SizeIn);
  }

  void PiCameraTesterBase ::
    connect_to_Schedin(
        const NATIVE_INT_TYPE portNum,
        Svc::InputSchedPort *const Schedin
    )
  {
    FW_ASSERT(portNum < this->getNum_to_Schedin(),static_cast<AssertArg>(portNum));
    this->m_to_Schedin[portNum].addCallPort(Schedin);
  }

  void PiCameraTesterBase ::
    connect_to_SendFrame(
        const NATIVE_INT_TYPE portNum,
        App::InputPiCameraFramePortPort *const SendFrame
    )
  {
    FW_ASSERT(portNum < this->getNum_to_SendFrame(),static_cast<AssertArg>(portNum));
    this->m_to_SendFrame[portNum].addCallPort(SendFrame);
  }

  void PiCameraTesterBase ::
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

  void PiCameraTesterBase ::
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

  void PiCameraTesterBase ::
    invoke_to_position(
        const NATIVE_INT_TYPE portNum,
        Fw::Time time,
        F64 latitude,
        F64 longitude,
        U16 altitude,
        U8 satellite
    )
  {
    FW_ASSERT(portNum < this->getNum_to_position(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_position(),static_cast<AssertArg>(portNum));
    this->m_to_position[portNum].invoke(
        time, latitude, longitude, altitude, satellite
    );
  }

  void PiCameraTesterBase ::
    invoke_to_barometerDataIn(
        const NATIVE_INT_TYPE portNum,
        U16 altitude,
        F32 pressure,
        F32 temperature
    )
  {
    FW_ASSERT(portNum < this->getNum_to_barometerDataIn(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_barometerDataIn(),static_cast<AssertArg>(portNum));
    this->m_to_barometerDataIn[portNum].invoke(
        altitude, pressure, temperature
    );
  }

  void PiCameraTesterBase ::
    invoke_to_SizeIn(
        const NATIVE_INT_TYPE portNum,
        U32 width,
        U32 height
    )
  {
    FW_ASSERT(portNum < this->getNum_to_SizeIn(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_SizeIn(),static_cast<AssertArg>(portNum));
    this->m_to_SizeIn[portNum].invoke(
        width, height
    );
  }

  void PiCameraTesterBase ::
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

  void PiCameraTesterBase ::
    invoke_to_SendFrame(
        const NATIVE_INT_TYPE portNum,
        U32 frame
    )
  {
    FW_ASSERT(portNum < this->getNum_to_SendFrame(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_SendFrame(),static_cast<AssertArg>(portNum));
    this->m_to_SendFrame[portNum].invoke(
        frame
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool PiCameraTesterBase ::
    isConnected_to_PingIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_PingIn(), static_cast<AssertArg>(portNum));
    return this->m_to_PingIn[portNum].isConnected();
  }

  bool PiCameraTesterBase ::
    isConnected_to_position(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_position(), static_cast<AssertArg>(portNum));
    return this->m_to_position[portNum].isConnected();
  }

  bool PiCameraTesterBase ::
    isConnected_to_barometerDataIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_barometerDataIn(), static_cast<AssertArg>(portNum));
    return this->m_to_barometerDataIn[portNum].isConnected();
  }

  bool PiCameraTesterBase ::
    isConnected_to_SizeIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_SizeIn(), static_cast<AssertArg>(portNum));
    return this->m_to_SizeIn[portNum].isConnected();
  }

  bool PiCameraTesterBase ::
    isConnected_to_Schedin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_Schedin(), static_cast<AssertArg>(portNum));
    return this->m_to_Schedin[portNum].isConnected();
  }

  bool PiCameraTesterBase ::
    isConnected_to_SendFrame(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_SendFrame(), static_cast<AssertArg>(portNum));
    return this->m_to_SendFrame[portNum].isConnected();
  }

  bool PiCameraTesterBase ::
    isConnected_to_CmdDisp(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_CmdDisp(), static_cast<AssertArg>(portNum));
    return this->m_to_CmdDisp[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Svc::InputPingPort *PiCameraTesterBase ::
    get_from_PingOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PingOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_PingOut[portNum];
  }

  Fw::InputComPort *PiCameraTesterBase ::
    get_from_PictureOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PictureOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_PictureOut[portNum];
  }

  Fw::InputCmdResponsePort *PiCameraTesterBase ::
    get_from_CmdStatus(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_CmdStatus(),static_cast<AssertArg>(portNum));
    return &this->m_from_CmdStatus[portNum];
  }

  Fw::InputCmdRegPort *PiCameraTesterBase ::
    get_from_CmdReg(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_CmdReg(),static_cast<AssertArg>(portNum));
    return &this->m_from_CmdReg[portNum];
  }

  Fw::InputTlmPort *PiCameraTesterBase ::
    get_from_Tlm(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Tlm(),static_cast<AssertArg>(portNum));
    return &this->m_from_Tlm[portNum];
  }

  Fw::InputTimePort *PiCameraTesterBase ::
    get_from_Time(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Time(),static_cast<AssertArg>(portNum));
    return &this->m_from_Time[portNum];
  }

  Fw::InputLogPort *PiCameraTesterBase ::
    get_from_Log(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Log(),static_cast<AssertArg>(portNum));
    return &this->m_from_Log[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *PiCameraTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    from_PingOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(callComp);
    PiCameraTesterBase* _testerBase =
      static_cast<PiCameraTesterBase*>(callComp);
    _testerBase->from_PingOut_handlerBase(
        portNum,
        key
    );
  }

  void PiCameraTesterBase ::
    from_PictureOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        Fw::ComBuffer &data,
        U32 context
    )
  {
    FW_ASSERT(callComp);
    PiCameraTesterBase* _testerBase =
      static_cast<PiCameraTesterBase*>(callComp);
    _testerBase->from_PictureOut_handlerBase(
        portNum,
        data, context
    );
  }

  void PiCameraTesterBase ::
    from_CmdStatus_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
  {
    PiCameraTesterBase* _testerBase =
      static_cast<PiCameraTesterBase*>(component);
    _testerBase->cmdResponseIn(opCode, cmdSeq, response);
  }

  void PiCameraTesterBase ::
    from_CmdReg_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode
    )
  {

  }

  void PiCameraTesterBase ::
    from_Tlm_static(
        Fw::PassiveComponentBase *const component,
        NATIVE_INT_TYPE portNum,
        FwChanIdType id,
        Fw::Time &timeTag,
        Fw::TlmBuffer &val
    )
  {
    PiCameraTesterBase* _testerBase =
      static_cast<PiCameraTesterBase*>(component);
    _testerBase->dispatchTlm(id, timeTag, val);
  }

  void PiCameraTesterBase ::
    from_Log_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    PiCameraTesterBase* _testerBase =
      static_cast<PiCameraTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void PiCameraTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    PiCameraTesterBase* _testerBase =
      static_cast<PiCameraTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void PiCameraTesterBase ::
    from_Time_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    PiCameraTesterBase* _testerBase =
      static_cast<PiCameraTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_PingOut->clear();
    this->fromPortHistory_PictureOut->clear();
  }

  // ----------------------------------------------------------------------
  // From port: PingOut
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
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
  // From port: PictureOut
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    pushFromPortEntry_PictureOut(
        Fw::ComBuffer &data,
        U32 context
    )
  {
    FromPortEntry_PictureOut _e = {
      data, context
    };
    this->fromPortHistory_PictureOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
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

  void PiCameraTesterBase ::
    from_PictureOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        Fw::ComBuffer &data,
        U32 context
    )
  {
    FW_ASSERT(portNum < this->getNum_from_PictureOut(),static_cast<AssertArg>(portNum));
    this->from_PictureOut_handler(
        portNum,
        data, context
    );
  }

  // ----------------------------------------------------------------------
  // Command response handling
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
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
  // Command: PiCam_TakePicture
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    sendCmd_PiCam_TakePicture(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = PiCameraComponentBase::OPCODE_PICAM_TAKEPICTURE + idBase;

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

  // ----------------------------------------------------------------------
  // Command: PiCam_SendLast
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    sendCmd_PiCam_SendLast(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = PiCameraComponentBase::OPCODE_PICAM_SENDLAST + idBase;

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

  // ----------------------------------------------------------------------
  // Command: PiCam_SetTimeInterval
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    sendCmd_PiCam_SetTimeInterval(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U8 timeInterval
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(timeInterval);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = PiCameraComponentBase::OPCODE_PICAM_SETTIMEINTERVAL + idBase;

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

  // ----------------------------------------------------------------------
  // Command: PiCam_SetSize
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    sendCmd_PiCam_SetSize(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U32 width,
        U32 height
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(width);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(height);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = PiCameraComponentBase::OPCODE_PICAM_SETSIZE + idBase;

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


  void PiCameraTesterBase ::
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

  void PiCameraTesterBase ::
    clearHistory()
  {
    this->cmdResponseHistory->clear();
    this->clearTlm();
    this->textLogHistory->clear();
    this->clearEvents();
    this->clearFromPortHistory();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Telemetry dispatch
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
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

      case PiCameraComponentBase::CHANNELID_PICAM_PICTURECNT:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing PiCam_PictureCnt: %d\n", _status);
          return;
        }
        this->tlmInput_PiCam_PictureCnt(timeTag, arg);
        break;
      }

      case PiCameraComponentBase::CHANNELID_PICAM_PICTURESIZE:
      {
        App::PictureSize arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing PiCam_PictureSize: %d\n", _status);
          return;
        }
        this->tlmInput_PiCam_PictureSize(timeTag, arg);
        break;
      }

      case PiCameraComponentBase::CHANNELID_PICAM_TIMEINTERVAL:
      {
        U8 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing PiCam_Timeinterval: %d\n", _status);
          return;
        }
        this->tlmInput_PiCam_Timeinterval(timeTag, arg);
        break;
      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void PiCameraTesterBase ::
    clearTlm(void)
  {
    this->tlmSize = 0;
    this->tlmHistory_PiCam_PictureCnt->clear();
    this->tlmHistory_PiCam_PictureSize->clear();
    this->tlmHistory_PiCam_Timeinterval->clear();
  }

  // ----------------------------------------------------------------------
  // Channel: PiCam_PictureCnt
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    tlmInput_PiCam_PictureCnt(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_PiCam_PictureCnt e = { timeTag, val };
    this->tlmHistory_PiCam_PictureCnt->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: PiCam_PictureSize
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    tlmInput_PiCam_PictureSize(
        const Fw::Time& timeTag,
        const App::PictureSize& val
    )
  {
    TlmEntry_PiCam_PictureSize e = { timeTag, val };
    this->tlmHistory_PiCam_PictureSize->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: PiCam_Timeinterval
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    tlmInput_PiCam_Timeinterval(
        const Fw::Time& timeTag,
        const U8& val
    )
  {
    TlmEntry_PiCam_Timeinterval e = { timeTag, val };
    this->tlmHistory_PiCam_Timeinterval->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
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

      case PiCameraComponentBase::EVENTID_PICAM_PICTURETAKEN:
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
        this->logIn_ACTIVITY_LO_PiCam_PictureTaken();

        break;

      }

      case PiCameraComponentBase::EVENTID_PICAM_POSITIONUPDATE:
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
        this->logIn_ACTIVITY_LO_PiCam_PositionUpdate();

        break;

      }

      case PiCameraComponentBase::EVENTID_PICAM_BAROMETERDATAUPDATE:
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
        FW_ASSERT(_numArgs == 3,_numArgs,3);

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

        F32 pressure;
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
        _status = args.deserialize(pressure);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U16 altitude;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U16),_argSize,sizeof(U16));
        }
#endif
        _status = args.deserialize(altitude);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_LO_PiCam_BarometerDataUpdate(temp, pressure, altitude);

        break;

      }

      case PiCameraComponentBase::EVENTID_PICAM_PICTUREERROR:
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
        FW_ASSERT(_numArgs == 1,_numArgs,1);

#endif
        U32 code;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(code);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_LO_PiCam_PictureError(code);

        break;

      }

      case PiCameraComponentBase::EVENTID_PICAM_SETTIMEINTERVAL:
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
        FW_ASSERT(_numArgs == 1,_numArgs,1);

#endif
        U8 timeInterval;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U8),_argSize,sizeof(U8));
        }
#endif
        _status = args.deserialize(timeInterval);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_LO_PiCam_SetTimeInterval(timeInterval);

        break;

      }

      case PiCameraComponentBase::EVENTID_PICAM_SETPICTURESIZE:
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
        U32 width;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(width);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U32 height;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(height);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_LO_PiCam_SetPictureSize(width, height);

        break;

      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void PiCameraTesterBase ::
    clearEvents(void)
  {
    this->eventsSize = 0;
    this->eventsSize_PiCam_PictureTaken = 0;
    this->eventsSize_PiCam_PositionUpdate = 0;
    this->eventHistory_PiCam_BarometerDataUpdate->clear();
    this->eventHistory_PiCam_PictureError->clear();
    this->eventHistory_PiCam_SetTimeInterval->clear();
    this->eventHistory_PiCam_SetPictureSize->clear();
  }

#if FW_ENABLE_TEXT_LOGGING

  // ----------------------------------------------------------------------
  // Text events
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
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

  void PiCameraTesterBase ::
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

  void PiCameraTesterBase ::
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
  // Event: PiCam_PictureTaken
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    logIn_ACTIVITY_LO_PiCam_PictureTaken(
        void
    )
  {
    ++this->eventsSize_PiCam_PictureTaken;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_PositionUpdate
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    logIn_ACTIVITY_LO_PiCam_PositionUpdate(
        void
    )
  {
    ++this->eventsSize_PiCam_PositionUpdate;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_BarometerDataUpdate
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    logIn_ACTIVITY_LO_PiCam_BarometerDataUpdate(
        F32 temp,
        F32 pressure,
        U16 altitude
    )
  {
    EventEntry_PiCam_BarometerDataUpdate e = {
      temp, pressure, altitude
    };
    eventHistory_PiCam_BarometerDataUpdate->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_PictureError
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    logIn_WARNING_LO_PiCam_PictureError(
        U32 code
    )
  {
    EventEntry_PiCam_PictureError e = {
      code
    };
    eventHistory_PiCam_PictureError->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_SetTimeInterval
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    logIn_ACTIVITY_LO_PiCam_SetTimeInterval(
        U8 timeInterval
    )
  {
    EventEntry_PiCam_SetTimeInterval e = {
      timeInterval
    };
    eventHistory_PiCam_SetTimeInterval->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_SetPictureSize
  // ----------------------------------------------------------------------

  void PiCameraTesterBase ::
    logIn_ACTIVITY_LO_PiCam_SetPictureSize(
        U32 width,
        U32 height
    )
  {
    EventEntry_PiCam_SetPictureSize e = {
      width, height
    };
    eventHistory_PiCam_SetPictureSize->push_back(e);
    ++this->eventsSize;
  }

} // end namespace App
