// ====================================================================== 
// \title  SenseHat.hpp
// \author root
// \brief  cpp file for SenseHat test harness implementation class
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
      SenseHatGTestBase("Tester", MAX_HISTORY_SIZE),
      component("SenseHat")
#else
      SenseHatGTestBase(MAX_HISTORY_SIZE),
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
    testCmdMS_GET_TM(void) 
  {

    //send MS_GET_TM command
    this->sendCmd_MS_GET_TM(0,10);
    this->component.doDispatch();

    //check event
    ASSERT_EVENTS_SIZE(0);
    ASSERT_EVENTS_MS_DATA_SIZE(0);

    //check port out
    ASSERT_FROM_PORT_HISTORY_SIZE(3);
    ASSERT_from_SHT_SIZE(1);    
    ASSERT_from_LPS_SIZE(1);
    ASSERT_from_ICM_SIZE(1);

    //check command
    ASSERT_CMD_RESPONSE_SIZE(1);
    // verify the command response was correct as expected
    ASSERT_CMD_RESPONSE(0,SenseHatComponentBase::OPCODE_MS_GET_TM,10,Fw::COMMAND_OK);

  }
  void Tester ::
    testSchedIn(void) 
  {
    
    //invoke sched in port 
    this->invoke_to_Schedin(0,0);
    this->component.doDispatch();

    //check event
    ASSERT_EVENTS_SIZE(0);
    ASSERT_EVENTS_MS_DATA_SIZE(0);

    //check port out
    ASSERT_FROM_PORT_HISTORY_SIZE(3);
    ASSERT_from_SHT_SIZE(1);    
    ASSERT_from_LPS_SIZE(1);
    ASSERT_from_ICM_SIZE(1);

  }


  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_SHT_handler(
        const NATIVE_INT_TYPE portNum,
        F32 temperature,
        F32 humidity
    )
  {
    this->pushFromPortEntry_SHT(temperature, humidity);
  }

  void Tester ::
    from_LPS_handler(
        const NATIVE_INT_TYPE portNum,
        F32 temperature,
        F32 pressure
    )
  {
    this->pushFromPortEntry_LPS(temperature, pressure);
  }

  void Tester ::
    from_ICM_handler(
        const NATIVE_INT_TYPE portNum,
        App::Angles &angles,
        App::Vector &gyro,
        App::Vector &accel,
        App::Vector &magn
    )
  {
    this->pushFromPortEntry_ICM(angles, gyro, accel, magn);
  }

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

    // Schedin
    this->connect_to_Schedin(
        0,
        this->component.get_Schedin_InputPort(0)
    );

    // PingIn
    this->connect_to_PingIn(
        0,
        this->component.get_PingIn_InputPort(0)
    );

    // CmdDisp
    this->connect_to_CmdDisp(
        0,
        this->component.get_CmdDisp_InputPort(0)
    );

    // SHT
    this->component.set_SHT_OutputPort(
        0, 
        this->get_from_SHT(0)
    );

    // LPS
    this->component.set_LPS_OutputPort(
        0, 
        this->get_from_LPS(0)
    );

    // ICM
    this->component.set_ICM_OutputPort(
        0, 
        this->get_from_ICM(0)
    );

    // PingOut
    this->component.set_PingOut_OutputPort(
        0, 
        this->get_from_PingOut(0)
    );

    // CmdStatus
    this->component.set_CmdStatus_OutputPort(
        0, 
        this->get_from_CmdStatus(0)
    );

    // CmdReg
    this->component.set_CmdReg_OutputPort(
        0, 
        this->get_from_CmdReg(0)
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
