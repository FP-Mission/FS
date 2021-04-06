// ======================================================================
// \title  EpsComponentImpl.hpp
// \author jonathan
// \brief  hpp file for Eps component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Eps_HPP
#define Eps_HPP

#include "App/Eps/EpsComponentAc.hpp"

namespace App {

class EpsComponentImpl : public EpsComponentBase {
   public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object Eps
    //!
    EpsComponentImpl(const char *const compName /*!< The component name*/
    );

    //! Initialize object Eps
    //!
    void init(const NATIVE_INT_TYPE queueDepth,  /*!< The queue depth*/
              const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Destroy object Eps
    //!
    ~EpsComponentImpl(void);

    PRIVATE :

        // ----------------------------------------------------------------------
        // Handler implementations for user-defined typed input ports
        // ----------------------------------------------------------------------

        //! Handler implementation for batteryVoltage
        //!
        void
        batteryVoltage_handler(
            const NATIVE_INT_TYPE portNum, /*!< The port number*/
            U16 voltage                    /*!< Battery voltage level in mV*/
        );

    PRIVATE :

        // ----------------------------------------------------------------------
        // Command handler implementations
        // ----------------------------------------------------------------------

        //! Implementation for Eps_SetWarningLevel command handler
        //! Set low battery level
        void
        Eps_SetWarningLevel_cmdHandler(
            const FwOpcodeType opCode, /*!< The opcode*/
            const U32 cmdSeq,          /*!< The command sequence number*/
            U16 voltage                /*!< Voltage in mV*/
        );

    //! Implementation for Eps_SetCriticalLevel command handler
    //! Set critical low battery level
    void Eps_SetCriticalLevel_cmdHandler(
        const FwOpcodeType opCode, /*!< The opcode*/
        const U32 cmdSeq,          /*!< The command sequence number*/
        U16 voltage                /*!< Voltage in mV*/
    );
};

}  // end namespace App

#endif
