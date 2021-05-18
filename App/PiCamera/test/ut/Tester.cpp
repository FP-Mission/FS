// ====================================================================== 
// \title  PiCamera.hpp
// \author root
// \brief  cpp file for PiCamera test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// 
// ====================================================================== 

#include "Tester.hpp"
#include "Os/FileSystem.hpp"
#include "App/Config/PiCameraConfig.hpp"

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
      PiCameraGTestBase("Tester", MAX_HISTORY_SIZE),
      component("PiCamera")
#else
      PiCameraGTestBase(MAX_HISTORY_SIZE),
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
    testCreatedDirectory(void) 
  {
    U32 sizeDirectories = 5;
    Fw::EightyCharString directories[sizeDirectories];
    U32 numFile = 0;
    Os::FileSystem::Status status = Os::FileSystem::readDirectory(BASE_DIRECTORY,sizeDirectories,
    directories,numFile); 

    printf("size %d\n",numFile);
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
    from_PictureOut_handler(
        const NATIVE_INT_TYPE portNum,
        U32 path
    )
  {
    this->pushFromPortEntry_PictureOut(path);
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // PingIn
    this->connect_to_PingIn(
        0,
        this->component.get_PingIn_InputPort(0)
    );

    // position
    this->connect_to_position(
        0,
        this->component.get_position_InputPort(0)
    );

    // barometerDataIn
    this->connect_to_barometerDataIn(
        0,
        this->component.get_barometerDataIn_InputPort(0)
    );

    // SizeIn
    this->connect_to_SizeIn(
        0,
        this->component.get_SizeIn_InputPort(0)
    );

    // Schedin
    this->connect_to_Schedin(
        0,
        this->component.get_Schedin_InputPort(0)
    );

    // CmdDisp
    this->connect_to_CmdDisp(
        0,
        this->component.get_CmdDisp_InputPort(0)
    );

    // PingOut
    this->component.set_PingOut_OutputPort(
        0, 
        this->get_from_PingOut(0)
    );

    // PictureOut
    this->component.set_PictureOut_OutputPort(
        0, 
        this->get_from_PictureOut(0)
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
