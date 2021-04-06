// ======================================================================
// \title  FlexTrakComponentImpl.cpp
// \author jonathan
// \brief  cpp file for FlexTrak component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <App/FlexTrak/FlexTrakComponentImpl.hpp>

#include "Fw/Types/BasicTypes.hpp"

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

FlexTrakComponentImpl ::FlexTrakComponentImpl(const char *const compName)
    : FlexTrakComponentBase(compName) {}

void FlexTrakComponentImpl ::init(const NATIVE_INT_TYPE queueDepth,
                                  const NATIVE_INT_TYPE instance) {
    FlexTrakComponentBase::init(queueDepth, instance);
}

FlexTrakComponentImpl ::~FlexTrakComponentImpl(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void FlexTrakComponentImpl ::PingIn_handler(const NATIVE_INT_TYPE portNum,
                                            U32 key) {
    // @todo Implement Ping logic
    PingOut_out(0, key);
}

void FlexTrakComponentImpl ::serialRecv_handler(const NATIVE_INT_TYPE portNum,
                                                Fw::Buffer &serBuffer,
                                                Drv::SerialReadStatus &status) {
    // TODO
}

void FlexTrakComponentImpl ::sendData_handler(const NATIVE_INT_TYPE portNum,
                                              Fw::Buffer &fwBuffer) {
    // TODO
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void FlexTrakComponentImpl ::FT_Version_cmdHandler(const FwOpcodeType opCode,
                                                   const U32 cmdSeq) {
    // @todo Implement version request
    this->log_ACTIVITY_LO_FT_Version(1);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

}  // end namespace App
