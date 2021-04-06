// ======================================================================
// \title  PredictorComponentImpl.cpp
// \author jonathan
// \brief  cpp file for Predictor component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/Predictor/PredictorComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  PredictorComponentImpl ::
    PredictorComponentImpl(
        const char *const compName
    ) : PredictorComponentBase(compName)
  {

  }

  void PredictorComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    PredictorComponentBase::init(queueDepth, instance);
  }

  PredictorComponentImpl ::
    ~PredictorComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void PredictorComponentImpl ::
    position_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Time time,
        I32 latitude,
        I32 longitude,
        U16 altitude,
        U8 satellite
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void PredictorComponentImpl ::
    Predi_SetPredictionRate_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 rate
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

} // end namespace App
