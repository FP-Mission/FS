// ====================================================================== 
// \title  Barometer.hpp
// \author root
// \brief  cpp file for Barometer test harness implementation class
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
      BarometerGTestBase("Tester", MAX_HISTORY_SIZE),
      component("Barometer")
#else
      BarometerGTestBase(MAX_HISTORY_SIZE),
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
    F32 temperatureTheoritical = 23.6;
    F32 pressureTheoritical = 900.7;
    U16 altitudeTheoritical = 920;

    this->invoke_to_DataIn(0,temperatureTheoritical, pressureTheoritical);
    this->component.doDispatch();

    // Event
    ASSERT_EVENTS_SIZE(0);
    ASSERT_EVENTS_MS_DATA_SIZE(0);
    //ASSERT_EVENTS_MS_DATA(0,temperatureTheoritical,pressureTheoritical,altitudeTheoritical);

    //telemetry
    ASSERT_TLM_SIZE(3);
    ASSERT_TLM_BAROMETER_TEMP_SIZE(1);
    ASSERT_TLM_BAROMETER_PRESS_SIZE(1);
    ASSERT_TLM_BAROMETER_ALT_SIZE(1);
    ASSERT_TLM_BAROMETER_TEMP(0,temperatureTheoritical);
    ASSERT_TLM_BAROMETER_PRESS(0,pressureTheoritical);
    ASSERT_TLM_BAROMETER_ALT(0,altitudeTheoritical);

    //port
    ASSERT_FROM_PORT_HISTORY_SIZE(1);
    ASSERT_from_DataOut_SIZE(1);
    ASSERT_from_DataOut(0,altitudeTheoritical,pressureTheoritical,temperatureTheoritical);
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

  void Tester ::
    from_DataOut_handler(
        const NATIVE_INT_TYPE portNum,
        U16 altitude,
        F32 pressure,
        F32 temperature
    )
  {
    this->pushFromPortEntry_DataOut(altitude, pressure, temperature);
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

    // DataOut
    this->component.set_DataOut_OutputPort(
        0, 
        this->get_from_DataOut(0)
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
