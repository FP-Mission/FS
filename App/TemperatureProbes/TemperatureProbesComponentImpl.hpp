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

class TemperatureProbesComponentImpl : public TemperatureProbesComponentBase {
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
    void init(const NATIVE_INT_TYPE queueDepth,  /*!< The queue depth*/
              const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Destroy object TemperatureProbes
    //!
    ~TemperatureProbesComponentImpl(void);

    PRIVATE :

        // ----------------------------------------------------------------------
        // Handler implementations for user-defined typed input ports
        // ----------------------------------------------------------------------

        //! Handler implementation for internal
        //!
        void
        internalIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                         I16 degree /*!< Temperature in °C*/
        );

    //! Handler implementation for external
    //!
    void externalIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                          I16 degree /*!< Temperature in °C*/
    );

    PRIVATE :

        // ----------------------------------------------------------------------
        // Command handler implementations
        // ----------------------------------------------------------------------

        //! Implementation for TempProb_SetInternalLevel command handler
        //! Set internal temperature warning level
        void
        TempProb_SetExternalHighLevel_cmdHandler(
            const FwOpcodeType opCode, /*!< The opcode*/
            const U32 cmdSeq,          /*!< The command sequence number*/
            I16 temperature            /*!< Temperature in °C*/
        );

    //! Implementation for TempProb_SetExternalLevel command handler
    //! Set external temperature warning level
    void TempProb_SetExternalLowLevel_cmdHandler(
        const FwOpcodeType opCode, /*!< The opcode*/
        const U32 cmdSeq,          /*!< The command sequence number*/
        I16 temperature            /*!< Temperature in °C*/
    );
    I16 highExternalTemp = 40;
    I16 lowExternalTemp = -10;
    bool limitTemp = true;
};

}  // end namespace App

#endif
