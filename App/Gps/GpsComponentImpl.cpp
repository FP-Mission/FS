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

GpsComponentImpl ::GpsComponentImpl(const char *const compName)
    : GpsComponentBase(compName) {}

void GpsComponentImpl ::init(const NATIVE_INT_TYPE instance) {
    GpsComponentBase::init(instance);
}

GpsComponentImpl ::~GpsComponentImpl(void) {}


// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void GpsComponentImpl ::positionIn_handler(
      const NATIVE_INT_TYPE portNum,
      Fw::Time time,
      F64 latitude,
      F64 longitude,
      U16 altitude,
      U8 satellite
  )
{
    //printf("[GPS] (%f, %f, %u) %u\n", latitude, longitude, altitude, satellite);
    // Generate Tlm for GPS position
    App::PositionSer pos;
    pos.setlatitude(latitude);
    pos.setlongitude(longitude);
    pos.setaltitude(altitude);
    pos.setsatellite(satellite);
    this->tlmWrite_Gps_Position(pos);
    // Forward GPS to PiCamera
    this->positionOut_out(0, time, latitude, longitude, altitude, satellite);
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void GpsComponentImpl ::Gps_SetFlightModeAltitude_cmdHandler(
    const FwOpcodeType opCode, const U32 cmdSeq, U16 altitude) {
    // TODO
    this->log_ACTIVITY_HI_Gps_Error();
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

}  // end namespace App
