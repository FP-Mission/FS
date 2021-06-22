// ======================================================================
// \title  GpsComponentImpl.hpp
// \author jonathan
// \brief  hpp file for Gps component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Gps_HPP
#define Gps_HPP

#include <Os/Mutex.hpp>

#include "App/Gps/GpsComponentAc.hpp"

#define GPS_LOCK_INTERVAL 10

namespace App {

class GpsComponentImpl : public GpsComponentBase {
   public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object Gps
    //!
    GpsComponentImpl(const char *const compName /*!< The component name*/
    );

    //! Initialize object Gps
    //!
    void init(const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Destroy object Gps
    //!
    ~GpsComponentImpl(void);

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      void Run_handler(NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context);

      //! Handler implementation for positionIn
      //!
      void positionIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time time, /*!< Measure time*/
          F64 latitude, /*!< Latitude in ? @todo*/
          F64 longitude, /*!< Longitude in ? @todo*/
          U16 altitude, /*!< Altitude in meters*/
          U8 satellite /*!< Satellite count*/
      );

    PRIVATE :

        // ----------------------------------------------------------------------
        // Command handler implementations
        // ----------------------------------------------------------------------

        //! Implementation for Gps_SetFlightModeAltitude command handler
        //! Set flight mode altitude. This is the altitude at which the GPS will
        //! switch from pedestrian mode (for more accuracy on the ground) to
        //! flight mode (to work above 18km)
        void
        Gps_GetLockState_cmdHandler(
            const FwOpcodeType opCode, /*!< The opcode*/
            const U32 cmdSeq          /*!< The command sequence number*/
        );

        Fw::Time lastGps;
        bool gpsLocked;
        Os::Mutex gpsMutex;
};

}  // end namespace App

#endif
