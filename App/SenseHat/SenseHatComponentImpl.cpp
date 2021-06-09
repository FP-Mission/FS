// ======================================================================
// \title  SenseHatComponentImpl.cpp
// \author root
// \brief  cpp file for SenseHat component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/SenseHat/SenseHatComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "wiringPi.h"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  SenseHatComponentImpl ::
    SenseHatComponentImpl(
        const char *const compName
    ) : SenseHatComponentBase(compName)
  {
      
  }

  void SenseHatComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    SenseHatComponentBase::init(queueDepth, instance);
  }

  SenseHatComponentImpl ::
    ~SenseHatComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void SenseHatComponentImpl ::
    Schedin_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    process();
  }

  void SenseHatComponentImpl ::
    PingIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    PingOut_out(portNum,key);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void SenseHatComponentImpl ::
    MS_GET_TM_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    process();
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);    
  }

  void SenseHatComponentImpl :: process(){
    shtc3.cycle();
    lps22.cycle();
    icm.cycle();

    IMU_ST_ANGLES_DATA anglesData = icm.getAngles();
    IMU_ST_SENSOR_DATA gyroData = icm.getGyro();
    IMU_ST_SENSOR_DATA accelData = icm.getAccel();
    IMU_ST_SENSOR_DATA magnData = icm.getMagn();


    this->angles.setRollPitchYaw(anglesData.fRoll, anglesData.fPitch, anglesData.fYaw);
    this->gyro.setXyz(gyroData.s16X, gyroData.s16Y, gyroData.s16Z);
    this->accel.setXyz(accelData.s16X ,accelData.s16Y ,accelData.s16Z);
    this->magn.setXyz(magnData.s16X, magnData.s16Y, magnData.s16Z);

    //log_ACTIVITY_LO_MS_DATA();

    ICM_out(0,angles, gyro, accel, magn);
    SHT_out(0,shtc3.getTemperatureValue(),shtc3.getHumidityValue());
    LPS_out(0,lps22.getTemperatureValue(),lps22.getPressureValue());
  }


} // end namespace App
