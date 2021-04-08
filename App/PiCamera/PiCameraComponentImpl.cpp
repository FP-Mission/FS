// ======================================================================
// \title  PiCameraComponentImpl.cpp
// \author jonathan
// \brief  cpp file for PiCamera component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <App/PiCamera/PiCameraComponentImpl.hpp>

#include "Fw/Types/BasicTypes.hpp"

// #include <raspicam.h>
#include <wiringPi.h>

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

PiCameraComponentImpl ::PiCameraComponentImpl(const char *const compName)
    : PiCameraComponentBase(compName) {}

void PiCameraComponentImpl ::init(const NATIVE_INT_TYPE queueDepth,
                                  const NATIVE_INT_TYPE instance) {
    PiCameraComponentBase::init(queueDepth, instance);
    
    wiringPiSetup();
    /*
    raspicam::RaspiCam Camera;
    if (!Camera.open())
        printf("Error opening camera\n");
    */

}

PiCameraComponentImpl ::~PiCameraComponentImpl(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void PiCameraComponentImpl ::PingIn_handler(const NATIVE_INT_TYPE portNum,
                                            U32 key) {
    // @todo Implement Ping logic
    PingOut_out(0, key);
}

void PiCameraComponentImpl ::position_handler(const NATIVE_INT_TYPE portNum,
                                              Fw::Time time, F64 latitude,
                                              F64 longitude, U16 altitude,
                                              U8 satellite) {
    // TODO
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void PiCameraComponentImpl ::PiCam_TakePicture_cmdHandler(
    const FwOpcodeType opCode, const U32 cmdSeq) {
    // @todo
    this->log_ACTIVITY_LO_PiCam_PictureTaken();
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

}  // end namespace App
