// ======================================================================
// \title  TemperatureProbesComponentImpl.hpp
// \author jonathan
// \brief  hpp file for TemperatureProbes component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef TemperatureProbes_HPP
#define TemperatureProbes_HPP

#include "App/TemperatureProbes/TemperatureProbesComponentAc.hpp"

namespace App {

  class TemperatureProbesComponentImpl :
    public TemperatureProbesComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object TemperatureProbes
      //!
      TemperatureProbesComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object TemperatureProbes
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object TemperatureProbes
      //!
      ~TemperatureProbesComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for internalTemperature
      //!
      void internalTemperature_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 degree /*!< Temperature in °C*/
      );

      //! Handler implementation for externalTemperature
      //!
      void externalTemperature_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 degree /*!< Temperature in °C*/
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for TempProb_SetInternalLevel command handler
      //! Set internal temperature warning level
      void TempProb_SetInternalLevel_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 temperature /*!< Temperature in °C*/
      );

      //! Implementation for TempProb_SetExternalLevel command handler
      //! Set external temperature warning level
      void TempProb_SetExternalLevel_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 temperature /*!< Temperature in °C*/
      );


    };

} // end namespace App

#endif
