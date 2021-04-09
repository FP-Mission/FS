// ======================================================================
// \title  ThermometerComponentImpl.cpp
// \author root
// \brief  cpp file for Thermometer component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/Thermometer/ThermometerComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ThermometerComponentImpl ::
    ThermometerComponentImpl(
        const char *const compName
    ) : ThermometerComponentBase(compName)
  {

  }

  void ThermometerComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    ThermometerComponentBase::init(queueDepth, instance);
  }

  ThermometerComponentImpl ::
    ~ThermometerComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ThermometerComponentImpl ::
    DataIn_handler(
        const NATIVE_INT_TYPE portNum,
        App::Angles &angles,
        App::Vector &gyro,
        App::Vector &accel,
        App::Vector &magn
    )
  {
    AnglesTlm angleTlm(angles.getRoll(),angles.getPitch(),angles.getYaw());
    VectorTlm gyroTlm(gyro.getX(), gyro.getY(), gyro.getZ());
    VectorTlm accelTlm(accel.getX(), accel.getY(), accel.getZ());
    VectorTlm magnTlm(magn.getX(), magn.getY(), magn.getZ());
    tlmWrite_THERMOMETER_ANGLES(angleTlm);
    tlmWrite_THERMOMETER_GYRO(gyroTlm);
    tlmWrite_THERMOMETER_ACCEL(accelTlm);
    tlmWrite_THERMOMETER_MAGN(magnTlm);
  }

  void ThermometerComponentImpl ::
    PingIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    PingOut_out(portNum,key);
  }

} // end namespace App
