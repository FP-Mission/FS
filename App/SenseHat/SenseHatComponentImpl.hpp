// ======================================================================
// \title  SenseHatComponentImpl.hpp
// \author root
// \brief  hpp file for SenseHat component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SenseHat_HPP
#define SenseHat_HPP

#include "App/SenseHat/SenseHatComponentAc.hpp"
#include "SHTC3/SHTC3.hpp"
#include "LPS22/LPS22.hpp"
#include "ICM/ICM.hpp"
#include "App/SenseHat/SenseHatPort/Vector.hpp"
#include "App/SenseHat/SenseHatPort/Angles.hpp"

namespace App {

  class SenseHatComponentImpl :
    public SenseHatComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SenseHat
      //!
      SenseHatComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object SenseHat
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object SenseHat
      //!
      ~SenseHatComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for Schedin
      //!
      void Schedin_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Handler implementation for PingIn
      //!
      void PingIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for MS_GET_TM command handler
      //! Send telemetry to SEnseHat
      void MS_GET_TM_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      void process();


      F32 SHTemperature=0.0f;
      F32 LPTemperature=0.0f;
      F32 humidity=0.0f;
      F32 pressure = 0.0f;
      Angles angles;
      Vector gyro, accel, magn;

      Icm icm;
      Shtc3 shtc3;
      Lps22 lps22;


      
    };

} // end namespace App

#endif
