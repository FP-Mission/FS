// ======================================================================
// \title  BarometerComponentImpl.cpp
// \author root
// \brief  cpp file for Barometer component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/Barometer/BarometerComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  BarometerComponentImpl ::
    BarometerComponentImpl(
        const char *const compName
    ) : BarometerComponentBase(compName)
  {

  }

  void BarometerComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    BarometerComponentBase::init(queueDepth, instance);
  }

  BarometerComponentImpl ::
    ~BarometerComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void BarometerComponentImpl ::
    DataIn_handler(
        const NATIVE_INT_TYPE portNum,
        F32 temperature,
        F32 pressure
    )
  {
    tlmWrite_BAROMETER_TEMP(temperature);
    tlmWrite_BAROMETER_PRESS(pressure);
  }

  void BarometerComponentImpl ::
    PingIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    PingOut_out(portNum,key);
  }

} // end namespace App
