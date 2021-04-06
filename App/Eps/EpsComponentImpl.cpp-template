// ======================================================================
// \title  EpsComponentImpl.cpp
// \author jonathan
// \brief  cpp file for Eps component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/Eps/EpsComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  EpsComponentImpl ::
    EpsComponentImpl(
        const char *const compName
    ) : EpsComponentBase(compName)
  {

  }

  void EpsComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    EpsComponentBase::init(queueDepth, instance);
  }

  EpsComponentImpl ::
    ~EpsComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void EpsComponentImpl ::
    batteryVoltage_handler(
        const NATIVE_INT_TYPE portNum,
        U16 voltage
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void EpsComponentImpl ::
    Eps_SetWarningLevel_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U16 voltage
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void EpsComponentImpl ::
    Eps_SetCriticalLevel_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U16 voltage
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

} // end namespace App
