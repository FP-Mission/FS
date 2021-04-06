// ======================================================================
// \title  RockBlockComponentImpl.cpp
// \author jonathan
// \brief  cpp file for RockBlock component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <App/RockBlock/RockBlockComponentImpl.hpp>

#include "Fw/Types/BasicTypes.hpp"

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

RockBlockComponentImpl ::RockBlockComponentImpl(const char *const compName)
    : RockBlockComponentBase(compName) {}

void RockBlockComponentImpl ::init(const NATIVE_INT_TYPE queueDepth,
                                   const NATIVE_INT_TYPE instance) {
    RockBlockComponentBase::init(queueDepth, instance);
}

RockBlockComponentImpl ::~RockBlockComponentImpl(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void RockBlockComponentImpl ::PingIn_handler(const NATIVE_INT_TYPE portNum,
                                             U32 key) {
    // @todo Implement Ping logic
    PingOut_out(0, key);
}

void RockBlockComponentImpl ::serialRecv_handler(
    const NATIVE_INT_TYPE portNum, Fw::Buffer &serBuffer,
    Drv::SerialReadStatus &status) {
    // TODO
}

}  // end namespace App
