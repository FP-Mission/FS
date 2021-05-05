// ======================================================================
// \title  ThermometerComponentImpl.hpp
// \author root
// \brief  hpp file for Thermometer component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Thermometer_HPP
#define Thermometer_HPP

#include "App/Thermometer/ThermometerComponentAc.hpp"

namespace App {

  class ThermometerComponentImpl :
    public ThermometerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Thermometer
      //!
      ThermometerComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object Thermometer
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object Thermometer
      //!
      ~ThermometerComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for DataIn
      //!
      void DataIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< sht temperature*/
          F32 humidity /*!< sht humidity*/
      );

      //! Handler implementation for PingIn
      //!
      void PingIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );


    };

} // end namespace App

#endif
