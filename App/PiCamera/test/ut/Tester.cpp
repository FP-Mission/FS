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
    testCreatedDirectories(void) 
  {
    Os::FileSystem::Status statusBase = Os::FileSystem::createDirectory(BASE_DIRECTORY); 
    Os::FileSystem::Status statusTlm = Os::FileSystem::createDirectory(TELEMETRY_DIRECTORY); 
    Os::FileSystem::Status statusPct = Os::FileSystem::createDirectory(PICTURE_DIRECTORY); 
    Os::FileSystem::Status statusPng = Os::FileSystem::createDirectory(PNG_DIRECTORY); 
    Os::FileSystem::Status statusJpg = Os::FileSystem::createDirectory(JPG_DIRECTORY); 
    Os::FileSystem::Status statusPpm = Os::FileSystem::createDirectory(PPM_DIRECTORY); 
    Os::FileSystem::Status statusBin = Os::FileSystem::createDirectory(BIN_DIRECTORY); 


    ASSERT_EQ(statusBase, Os::FileSystem::ALREADY_EXISTS);
    ASSERT_EQ(statusTlm, Os::FileSystem::ALREADY_EXISTS);
    ASSERT_EQ(statusPct, Os::FileSystem::ALREADY_EXISTS);
    ASSERT_EQ(statusPng, Os::FileSystem::ALREADY_EXISTS);
    ASSERT_EQ(statusJpg, Os::FileSystem::ALREADY_EXISTS);
    ASSERT_EQ(statusPpm, Os::FileSystem::ALREADY_EXISTS);
    ASSERT_EQ(statusBin, Os::FileSystem::ALREADY_EXISTS);
  }

  void Tester::testFile(void){
    std::ostringstream osTelemetry, dataTheoritical;
    osTelemetry << TELEMETRY_DIRECTORY << "telemetry.csv";

    dataTheoritical<< "id" <<","<<"Timecode" <<","<< "AltitudeGPS" <<","<< "AltitudeBaro" << 
    ","<<"Temperature"<<","<< "Pressure"<<","<< "Longitude" <<","<< "Latitude" <<
    ","<< "FlexInternTemp" <<","<< "FlexExternTemp" << "\n";

    std::ifstream f(osTelemetry.str());
    std::string dataEmpirical;
    std::getline(f, dataEmpirical);
    ASSERT_STRCASEEQ(dataTheoritical.str().c_str(),dataEmpirical.c_str()); 


    this->component.getNumberOfLine(osTelemetry);

    //ASSERT_EQ(this->component.nbPicture,0);

  }

  void Tester::testBarometerPort(void){
    U16 alt = 1000;
    F32 pressure = 1000.4;
    F32 temperature = 34.5;
    this->invoke_to_barometerDataIn(0,alt,pressure,temperature);

    ASSERT_EQ(this->component.altitudeBaro,alt);
    ASSERT_FLOAT_EQ(this->component.pressure,pressure);
    ASSERT_FLOAT_EQ(this->component.temperature,temperature);


    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_PiCam_BarometerDataUpdate_SIZE(1);
    ASSERT_EVENTS_PiCam_BarometerDataUpdate(0,temperature,pressure,alt);
    this->clearHistory();
  }

  void Tester::testPositionPort(void){
    Fw::Time time;
    F64 latitude;
    F64 longitude;
    U16 altitude;
    U8 satellite;
    this->invoke_to_position(0,time,latitude,longitude,altitude,satellite);

    ASSERT_EQ(this->component.altitudeGps,altitude);
    ASSERT_DOUBLE_EQ(this->component.latitude,latitude);
    ASSERT_DOUBLE_EQ(this->component.longitude,longitude);
    ASSERT_EQ(this->component.satellite,satellite);


    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_PiCam_PositionUpdate_SIZE(1);
    this->clearHistory();

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
        Fw::ComBuffer &data,
        U32 context
    )
  {
    this->pushFromPortEntry_PictureOut(data, context);
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

    // SendFrame
    this->connect_to_SendFrame(
        0,
        this->component.get_SendFrame_InputPort(0)
    );

    // tempProbeInternal
    this->connect_to_tempProbeInternal(
        0,
        this->component.get_tempProbeInternal_InputPort(0)
    );

    // tempProbeExternal
    this->connect_to_tempProbeExternal(
        0,
        this->component.get_tempProbeExternal_InputPort(0)
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
