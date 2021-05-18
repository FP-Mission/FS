// ======================================================================
// \title  TemperatureProbesComponentImpl.cpp
// \author jonathan
// \brief  cpp file for TemperatureProbes component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <App/TemperatureProbes/TemperatureProbesComponentImpl.hpp>

#include "Fw/Types/BasicTypes.hpp"

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

TemperatureProbesComponentImpl ::TemperatureProbesComponentImpl(
    const char *const compName)
    : TemperatureProbesComponentBase(compName) {}

void TemperatureProbesComponentImpl ::init(const NATIVE_INT_TYPE queueDepth,
                                           const NATIVE_INT_TYPE instance) {
    TemperatureProbesComponentBase::init(queueDepth, instance);
}

TemperatureProbesComponentImpl ::~TemperatureProbesComponentImpl(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void TemperatureProbesComponentImpl ::internal_handler(
    const NATIVE_INT_TYPE portNum, I16 degree) {
    printf("[TemperatureProbes] Internal temperature: %d\n", degree);
    tlmWrite_TempProb_InternalTemperature(degree);
}

void TemperatureProbesComponentImpl ::external_handler(
    const NATIVE_INT_TYPE portNum, I16 degree) {
    printf("[TemperatureProbes] External temperature: %d\n", degree);
    tlmWrite_TempProb_ExternalTemperature(degree);
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void TemperatureProbesComponentImpl ::TempProb_SetInternalLevel_cmdHandler(
    const FwOpcodeType opCode, const U32 cmdSeq, I16 temperature) {
    // @todo
    this->log_WARNING_HI_TempPro_LowInternalWarning(2);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

void TemperatureProbesComponentImpl ::TempProb_SetExternalLevel_cmdHandler(
    const FwOpcodeType opCode, const U32 cmdSeq, I16 temperature) {
    // @todo
    this->log_WARNING_HI_TempPro_LowExternalWarning(-15);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

}  // end namespace App
