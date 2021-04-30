// ======================================================================
// \title  MotionTrackingComponentImpl.cpp
// \author root
// \brief  cpp file for MotionTracking component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/MotionTracking/MotionTrackingComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  MotionTrackingComponentImpl ::
    MotionTrackingComponentImpl(
        const char *const compName
    ) : MotionTrackingComponentBase(compName)
  {

  }

  void MotionTrackingComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    MotionTrackingComponentBase::init(queueDepth, instance);
  }

  MotionTrackingComponentImpl ::
    ~MotionTrackingComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void MotionTrackingComponentImpl ::
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
    tlmWrite_MOTIONTRACKING_ANGLES(angleTlm);
    tlmWrite_MOTIONTRACKING_GYRO(gyroTlm);
    tlmWrite_MOTIONTRACKING_ACCEL(accelTlm);
    tlmWrite_MOTIONTRACKING_MAGN(magnTlm);
    log_ACTIVITY_LO_MS_DATA();
  }

  void MotionTrackingComponentImpl ::
    PingIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    PingOut_out(portNum,key);
  }

} // end namespace App
