// ======================================================================
// \title  GpsComponentImpl.cpp
// \author jonathan
// \brief  cpp file for Gps component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/Gps/GpsComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  GpsComponentImpl ::
    GpsComponentImpl(
        const char *const compName
    ) : GpsComponentBase(compName)
  {

  }

  void GpsComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    GpsComponentBase::init(instance);
  }

  GpsComponentImpl ::
    ~GpsComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void GpsComponentImpl ::
    Gps_SetFlightModeAltitude_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U16 altitude
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

} // end namespace App
