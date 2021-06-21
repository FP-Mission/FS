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

#include <Fw/Tlm/PositionSerializable/PositionSerializableCustom.hpp>

#define SLOT_SIZE 100
#define SLOT_COUNT 600 // 60000 / SLOT_SIZE

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

    private:

    struct Delta_t {
        F64 latitude;
        F64 longitude;
    };

    typedef U16 CDA_t;
    typedef U16 Slot_t;

    U16 slotSize = 100;
    U16 slotCount = 60000;
    FlightMode flightMode;
    
    App::PositionSerCustom previousPosition; 
    U32 minimumAltitude;
    U32 maximumAltitude;
    F32 ascentRate;
    F32 landingAltitude;
    F64 landingLatitude;
    F64 landingLongitude;
    U8 pollPeriod;
    U8 counter;
    CDA_t CDA;

    Delta_t deltas[SLOT_COUNT];

    U16 /* Slot_t */ getSlot(F32 altitude);
    F32 calculateAirDensity(F32 altitude);
    F32 calculateDescentRate(F32 weight, F32 CDTimesArea, F32 altitude);
    U16 /* CDA_t */ calculateCDA(F32 weight, F32 altitude, F32 descentRate);
    void addGpsPosition(App::PositionSerCustom position, App::PositionSerCustom &result, U64 &timeTillLanding);
    void calculateLandingPosition(App::PositionSerCustom position, App::PositionSerCustom &predictedPosition, U64 timeTillLanding);

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
