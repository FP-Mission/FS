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

#include "App/Gps/GpsComponentAc.hpp"

namespace App {

  class GpsComponentImpl :
    public GpsComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Gps
      //!
      GpsComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object Gps
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object Gps
      //!
      ~GpsComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for Gps_SetFlightModeAltitude command handler
      //! Set flight mode altitude. This is the altitude at which the GPS will switch from pedestrian mode (for more accuracy on the ground) to flight mode (to work above 18km)
      void Gps_SetFlightModeAltitude_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          I16 altitude /*!< Altitude in meters*/
      );


    };

} // end namespace App

#endif
