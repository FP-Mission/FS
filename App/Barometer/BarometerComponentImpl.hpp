// ======================================================================
// \title  BarometerComponentImpl.hpp
// \author root
// \brief  hpp file for Barometer component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Barometer_HPP
#define Barometer_HPP

#include "App/Barometer/BarometerComponentAc.hpp"

namespace App {

  class BarometerComponentImpl :
    public BarometerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Barometer
      //!
      BarometerComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object Barometer
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object Barometer
      //!
      ~BarometerComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for DataIn
      //!
      void DataIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< lps temperature*/
          F32 pressure /*!< lps humidity*/
      );

      //! Handler implementation for PingIn
      //!
      void PingIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      U16 getAltitude(F32 pressure);


    };

} // end namespace App

#endif
