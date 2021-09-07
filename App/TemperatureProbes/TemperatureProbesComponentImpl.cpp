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

void TemperatureProbesComponentImpl ::internalIn_handler(
    const NATIVE_INT_TYPE portNum, I16 degree) {
    //printf("[TemperatureProbes] Internal temperature: %d\n", degree);
    //internalOut_out(0, degree);
    //tlmWrite_TempProb_InternalTemperature(degree);
}

void TemperatureProbesComponentImpl ::externalIn_handler(
    const NATIVE_INT_TYPE portNum, I16 degree) {
    //printf("[TemperatureProbes] External temperature: %d\n", degree);
    //externalOut_out(0, degree);
    if(degree >= highExternalTemp && limitTemp){
        log_WARNING_HI_TempPro_HighExternalWarning(degree);
        limitTemp = false;
    }
    else if(degree <= lowExternalTemp && limitTemp){
        log_WARNING_HI_TempPro_LowExternalWarning(degree);
        limitTemp = false;
    }

    if(degree < highExternalTemp && degree > lowExternalTemp){
        limitTemp = true;
    }
    this->tlmWrite_TempProb_ExternalHighTemperature(highExternalTemp);
    this->tlmWrite_TempProb_ExternalLowTemperature(lowExternalTemp);
    tlmWrite_TempProb_ExternalTemperature(degree);
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void TemperatureProbesComponentImpl ::TempProb_SetExternalHighLevel_cmdHandler(
    const FwOpcodeType opCode, const U32 cmdSeq, I16 temperature) {
    // @todo
    this->log_ACTIVITY_LO_TempPro_TempSet(temperature);
    this->tlmWrite_TempProb_ExternalHighTemperature(temperature);
    this->highExternalTemp = temperature;
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

void TemperatureProbesComponentImpl ::TempProb_SetExternalLowLevel_cmdHandler(
    const FwOpcodeType opCode, const U32 cmdSeq, I16 temperature) {
    // @todo
    this->log_ACTIVITY_LO_TempPro_TempSet(temperature);
    this->tlmWrite_TempProb_ExternalLowTemperature(temperature);
    this->lowExternalTemp = temperature;
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

}  // end namespace App
