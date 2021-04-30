// ====================================================================== 
// \title  MotionTracking.hpp
// \author root
// \brief  cpp file for MotionTracking test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// 
// ====================================================================== 

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10
#define QUEUE_DEPTH 10

namespace App {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
    Tester(void) : 
#if FW_OBJECT_NAMES == 1
      MotionTrackingGTestBase("Tester", MAX_HISTORY_SIZE),
      component("MotionTracking")
#else
      MotionTrackingGTestBase(MAX_HISTORY_SIZE),
      component()
#endif
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester(void) 
  {
    
  }

  // ----------------------------------------------------------------------
  // Tests 
  // ----------------------------------------------------------------------

  void Tester ::
    testDataIn(void) 
  {
    Angles anglesTheoritical(12.0,45.9,34.8);
    Vector gyroTheoritical(12,-34,344);
    Vector accelTheoritical(-45,567,34);
    Vector magnTheoritical(345,4674,-3575);

    AnglesTlm angleTlmTheoritical(anglesTheoritical.getRoll(),anglesTheoritical.getPitch(),anglesTheoritical.getYaw());
    VectorTlm gyroTlmTheoritical(gyroTheoritical.getX(), gyroTheoritical.getY(), gyroTheoritical.getZ());
    VectorTlm accelTlmTheoritical(accelTheoritical.getX(), accelTheoritical.getY(), accelTheoritical.getZ());
    VectorTlm magnTlmTheoritical(magnTheoritical.getX(), magnTheoritical.getY(), magnTheoritical.getZ());

    this->invoke_to_DataIn(0,anglesTheoritical, gyroTheoritical,accelTheoritical,magnTheoritical);
    this->component.doDispatch();

    // Event
    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_MS_DATA_SIZE(1);

    //telemetry
    ASSERT_TLM_SIZE(4);
    ASSERT_TLM_MOTIONTRACKING_ANGLES_SIZE(1);
    ASSERT_TLM_MOTIONTRACKING_GYRO_SIZE(1);
    ASSERT_TLM_MOTIONTRACKING_ACCEL_SIZE(1);
    ASSERT_TLM_MOTIONTRACKING_MAGN_SIZE(1);

    ASSERT_TLM_MOTIONTRACKING_ANGLES(0,angleTlmTheoritical);
    ASSERT_TLM_MOTIONTRACKING_GYRO(0,gyroTlmTheoritical);
    ASSERT_TLM_MOTIONTRACKING_ACCEL(0,accelTlmTheoritical);
    ASSERT_TLM_MOTIONTRACKING_MAGN(0,magnTlmTheoritical);

  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_PingOut_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    this->pushFromPortEntry_PingOut(key);
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // DataIn
    this->connect_to_DataIn(
        0,
        this->component.get_DataIn_InputPort(0)
    );

    // PingIn
    this->connect_to_PingIn(
        0,
        this->component.get_PingIn_InputPort(0)
    );

    // PingOut
    this->component.set_PingOut_OutputPort(
        0, 
        this->get_from_PingOut(0)
    );

    // Tlm
    this->component.set_Tlm_OutputPort(
        0, 
        this->get_from_Tlm(0)
    );

    // Time
    this->component.set_Time_OutputPort(
        0, 
        this->get_from_Time(0)
    );

    // Log
    this->component.set_Log_OutputPort(
        0, 
        this->get_from_Log(0)
    );

    // LogText
    this->component.set_LogText_OutputPort(
        0, 
        this->get_from_LogText(0)
    );




  }

  void Tester ::
    initComponents(void) 
  {
    this->init();
    this->component.init(
        QUEUE_DEPTH, INSTANCE
    );
  }

} // end namespace App
