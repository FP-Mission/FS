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
#include <Fw/Buffer/Buffer.hpp>

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
    //log_ACTIVITY_LO_MS_TM_RECV_TEMP(12.6f);
    //tlmWrite_SENSE_LAST_TM_DATA(12.8f);
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
    shtc3.cycle();
    lps22.cycle();
    log_ACTIVITY_LO_MS_DATA_TEST(lps22.getPressureValue());
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
    
  }

} // end namespace App
