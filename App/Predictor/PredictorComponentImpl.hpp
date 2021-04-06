// ======================================================================
// \title  PredictorComponentImpl.hpp
// \author jonathan
// \brief  hpp file for Predictor component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Predictor_HPP
#define Predictor_HPP

#include "App/Predictor/PredictorComponentAc.hpp"

namespace App {

class PredictorComponentImpl : public PredictorComponentBase {
   public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object Predictor
    //!
    PredictorComponentImpl(const char *const compName /*!< The component name*/
    );

    //! Initialize object Predictor
    //!
    void init(const NATIVE_INT_TYPE queueDepth,  /*!< The queue depth*/
              const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Destroy object Predictor
    //!
    ~PredictorComponentImpl(void);

    PRIVATE :

        // ----------------------------------------------------------------------
        // Handler implementations for user-defined typed input ports
        // ----------------------------------------------------------------------

        //! Handler implementation for position
        //!
        void
        position_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                         Fw::Time time,                 /*!< Measure time*/
                         F64 latitude,  /*!< Latitude in ? @todo*/
                         F64 longitude, /*!< Longitude in ? @todo*/
                         U16 altitude,  /*!< Altitude in meters*/
                         U8 satellite   /*!< Satellite count*/
        );

    PRIVATE :

        // ----------------------------------------------------------------------
        // Command handler implementations
        // ----------------------------------------------------------------------

        //! Implementation for Predi_SetPredictionRate command handler
        //! Set prediction rate
        void
        Predi_SetPredictionRate_cmdHandler(
            const FwOpcodeType opCode, /*!< The opcode*/
            const U32 cmdSeq,          /*!< The command sequence number*/
            U8 rate /*!< Prediction rate. Set to 0 to disable. 1 means each time
                       the position is sent to the predictor it will estimate
                       landing position.*/
        );
};

}  // end namespace App

#endif
