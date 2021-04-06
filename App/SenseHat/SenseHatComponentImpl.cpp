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

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include"SHTC3.h"

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
    char buf[] = { 0,0};
    int fd=wiringPiI2CSetup(SHTC3_I2C_ADDRESS);
    wiringPiI2CWriteReg8(fd,buf[0],buf[1]);   
  }

  void SenseHatComponentImpl ::
    PingIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    // TODO
  }

} // end namespace App
