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

#include <math.h>

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

PredictorComponentImpl ::PredictorComponentImpl(const char *const compName)
    : PredictorComponentBase(compName) {}

void PredictorComponentImpl ::init(const NATIVE_INT_TYPE queueDepth,
                                   const NATIVE_INT_TYPE instance) {
    PredictorComponentBase::init(queueDepth, instance);
    this->flightMode = App::FlightMode::FM_IDLE;
    this->previousPosition.setlatitude(0);
    this->previousPosition.setlongitude(0);
    this->previousPosition.setaltitude(0);
    this->previousPosition.setsatellite(0);
    this->minimumAltitude = 0;
    this->maximumAltitude = 0;
    this->ascentRate = 0;
    this->landingAltitude = 200;    // @todo Define
    this->landingLatitude = 0.0;
    this->landingLongitude = 0.0;
    this->pollPeriod = 5;
    this->counter = 0;
    this->CDA = 0.7; // @todo Define
    for (U16 i = 0; i < SLOT_COUNT; i ++) {
        this->deltas[i].latitude = 0;
        this->deltas[i].longitude = 0;
    }
}

PredictorComponentImpl ::~PredictorComponentImpl(void) {}


U16 /* Slot_t */ PredictorComponentImpl ::getSlot(F32 altitude) {
    Slot_t slot = Slot_t(altitude / SLOT_SIZE);

    if (slot < 0) {
        slot = 0;
    }
    if (slot >= SLOT_SIZE) {
        slot = SLOT_SIZE - 1;
    }

    return slot;
}

F32 PredictorComponentImpl ::calculateAirDensity(F32 altitude) {
    F32 temperature = 0.0;
    F32 pressure = 0.0;
    if (altitude < 11000.0) {
        // below 11Km - Troposphere
        temperature = 15.04 - (0.00649 * altitude);
        pressure = 101.29 * pow((temperature + 273.1) / 288.08, 5.256);
    } else if (altitude < 25000.0) {
        // between 11Km and 25Km - lower Stratosphere
        temperature = -56.46;
        pressure = 22.65 * exp(1.73 - ( 0.000157 * altitude));
    } else {
        // above 25Km - upper Stratosphere
        temperature = -131.21 + (0.00299 * altitude);
        pressure = 2.488 * pow((temperature + 273.1) / 216.6, -11.388);
    }
    // @todo Check divideBy0
    return pressure / (0.2869 * (temperature + 273.1));
}

F32 PredictorComponentImpl ::calculateDescentRate(F32 weight, F32 CDTimesArea, F32 altitude) {
    F32 density = this->calculateAirDensity(altitude);
	// @todo Check divideBy0
    return sqrt((weight * 9.81)/(0.5 * density * CDTimesArea));
}

U16 /* CDA_t */ PredictorComponentImpl ::calculateCDA(F32 weight, F32 altitude, F32 descentRate) {
    if (descentRate > 0.0) {
        F32 density = this->calculateAirDensity(altitude);

        // printf("Alt %.0lf, Rate %.1lf, CDA %.1lf\n", altitude, descentRate, (weight * 9.81)/(0.5 * density * descentRate * descentRate))

        // @todo Check divideBy0
        return (weight * 9.81)/(0.5 * density * descentRate * descentRate);
    } else {
        return this->CDA;
    }
}

void PredictorComponentImpl ::addGpsPosition(App::PositionSerCustom position, 
    App::PositionSerCustom &result, U64 &timeTillLanding) {
    
    if (position.getsatellite() >= 4) {
        
        this->counter += 1;

        if (this->counter >= this->pollPeriod) {
            this->counter = 0;
            
            if (position.getaltitude() <= 0) {
                this->ascentRate = 0;
            } else {
                this->ascentRate = this->ascentRate * 0.7 + (position.getaltitude() - this->previousPosition.getaltitude()) * 0.3;
            }
            
            if ((position.getaltitude() < this->minimumAltitude) || (this->minimumAltitude == 0)) {
                this->minimumAltitude = position.getaltitude();
            }
            
            if (position.getaltitude() > this->maximumAltitude) {
                this->maximumAltitude = position.getaltitude();
            }

            // Detect launching
            if ((this->ascentRate >= 1.0) && 
                (position.getaltitude() > (this->minimumAltitude + 150)) && 
                (this->flightMode == App::FlightMode::FM_IDLE)) {
                this->flightMode = App::FlightMode::FM_LAUNCHED;
                printf("*** LAUNCHED ***"); // @todo replace by event
            }

            // Detect descending
            if ((this->ascentRate < -10.0) && 
                (this->maximumAltitude >= (this->minimumAltitude + 2000)) &&
                (this->flightMode == App::FlightMode::FM_LAUNCHED)) {
                this->flightMode = App::FlightMode::FM_DESCENDING;
                printf("*** DESCENDING ***"); // @todo replace by event
            }

            // Detect landing
            if ((this->ascentRate >= -0.1) &&
                (position.getaltitude() <= (this->landingAltitude + 2000)) &&
                (this->flightMode == App::FlightMode::FM_DESCENDING)) {
                this->flightMode = App::FlightMode::FM_LANDED;
                printf("*** LANDED ***");  // @todo replace by event
            }
                
            if (this->flightMode == App::FlightMode::FM_LAUNCHED) {
                // Going up - store deltas
                
                Slot_t slot = this->getSlot(position.getaltitude() / 2 + this->previousPosition.getaltitude() / 2);

                // Deltas are scaled to be horizontal distance per second (i.e. speed)
                this->deltas[slot].latitude = (position.getlatitude() - this->previousPosition.getlatitude()) / this->pollPeriod;
                this->deltas[slot].longitude = (position.getlongitude() - this->previousPosition.getlongitude()) / this->pollPeriod;
                
                // printf("Slot " + str(slot) + " = " + str(Position['alt']) + "," + str(this->deltas[slot].latitude) + "," + str(this->deltas[slot].longitude))
            } else if (this->flightMode == App::FlightMode::FM_DESCENDING) {
                // Coming down - try and calculate how well chute is doing

                this->CDA = (this->CDA * 4 + this->calculateCDA(1.0, position.getaltitude() / 2 + this->previousPosition.getaltitude() / 2, (this->previousPosition.getaltitude() - position.getaltitude()) / this->pollPeriod)) / 5;
            }
            
            if ((this->flightMode == App::FlightMode::FM_LAUNCHED) || (this->flightMode == App::FlightMode::FM_DESCENDING)) {
                this->calculateLandingPosition(position, result, timeTillLanding);

                // GPS->PredictedLandingSpeed = CalculateDescentRate(Config.payload_weight, GPS->CDA, Config.LandingAltitude)
            
                // printf("Expected Descent Rate = %4.1lf (now) %3.1lf (landing), time till landing %d\n", 
                        // CalculateDescentRate(Config.payload_weight, GPS->CDA, GPS->Altitude),
                        // GPS->PredictedLandingSpeed,
                        // GPS->TimeTillLanding)

                // printf("Current    %f, %f, alt %" PRId32 "\n", GPS->Latitude, GPS->Longitude, GPS->Altitude)
                // printf("Prediction %f, %f, CDA %lf\n", GPS->PredictedLatitude, GPS->PredictedLongitude, GPS->CDA)
            }

            //printf('PREDICTOR: ' + str(Position['time']) + ', ' + "::.5f}".format(Position['lat']) + ', ' + "{:.5f}".//format(Position['lon']) + ', ' + str(Position['alt']) + ', ' + str(Position['sats']))

            this->previousPosition = position;
        }
    }            
}

void PredictorComponentImpl ::calculateLandingPosition(App::PositionSerCustom position, 
    App::PositionSerCustom &predictedPosition, U64 timeTillLanding) {
    
    timeTillLanding = 0;
	
    Slot_t slot = this->getSlot(position.getaltitude());
    F32 distanceInSlot = position.getaltitude() + 1 - slot * SLOT_SIZE;

    while (position.getaltitude() > this->landingAltitude) {
        slot = this->getSlot(position.getaltitude());
    
        if (slot == this->getSlot(this->landingAltitude)) {
            distanceInSlot = position.getaltitude() - this->landingAltitude;
        }
        
        F32 descentRate = this->calculateDescentRate(1.0, this->CDA, position.getaltitude());
        
        F32 timeInSlot = distanceInSlot / descentRate;
        
        predictedPosition.setlatitude(predictedPosition.getlatitude() + this->deltas[slot].latitude * timeInSlot);
        predictedPosition.setlongitude(predictedPosition.getlongitude() + this->deltas[slot].longitude * timeInSlot);
        
        // printf("SLOT %d: alt %lu, lat=%lf, long=%lf, rate=%lf, dist=%lu, time=%lf\n", slot, position.getaltitude(), predictedPosition.latitude, predictedPosition.longitude, descentRate, distanceInSlot, timeInSlot);
        
        timeTillLanding += timeInSlot;
        position.setaltitude(position.getaltitude() - distanceInSlot);
        distanceInSlot = SLOT_SIZE;
    }
}
    

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void PredictorComponentImpl ::position_handler(const NATIVE_INT_TYPE portNum,
                                               Fw::Time time, F64 latitude,
                                               F64 longitude, U16 altitude,
                                               U8 satellite) {
    // @todo
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void PredictorComponentImpl ::Predi_SetPredictionRate_cmdHandler(
    const FwOpcodeType opCode, const U32 cmdSeq, U8 rate) {
    // @todo
    this->log_ACTIVITY_HI_Predi_FlightMode(FlightMode::FM_LANDED);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
}

}  // end namespace App
