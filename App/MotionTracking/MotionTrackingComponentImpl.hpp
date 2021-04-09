// ======================================================================
// \title  MotionTrackingComponentImpl.hpp
// \author root
// \brief  hpp file for MotionTracking component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef MotionTracking_HPP
#define MotionTracking_HPP

#include "App/MotionTracking/MotionTrackingComponentAc.hpp"

namespace App {

  class MotionTrackingComponentImpl :
    public MotionTrackingComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object MotionTracking
      //!
      MotionTrackingComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object MotionTracking
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object MotionTracking
      //!
      ~MotionTrackingComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for DataIn
      //!
      void DataIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          App::Angles &angles, 
          App::Vector &gyro, 
          App::Vector &accel, 
          App::Vector &magn 
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
