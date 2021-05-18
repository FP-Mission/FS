// ======================================================================
// \title  PiCameraComponentImpl.hpp
// \author jonathan
// \brief  hpp file for PiCamera component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef PiCamera_HPP
#define PiCamera_HPP

#include "App/PiCamera/PiCameraComponentAc.hpp"

namespace App {

class PiCameraComponentImpl : public PiCameraComponentBase {
   public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object PiCamera
    //!
    PiCameraComponentImpl(const char *const compName /*!< The component name*/
    );

    //! Initialize object PiCamera
    //!
    void init(const NATIVE_INT_TYPE queueDepth,  /*!< The queue depth*/
              const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Destroy object PiCamera
    //!
    ~PiCameraComponentImpl(void);

    PRIVATE :

        // ----------------------------------------------------------------------
        // Handler implementations for user-defined typed input ports
        // ----------------------------------------------------------------------

        //! Handler implementation for PingIn
        //!
        void
        PingIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                       U32 key /*!< Value to return to pinger*/
        );

    //! Handler implementation for position
    //!
    void position_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                          Fw::Time time,                 /*!< Measure time*/
                          F64 latitude,  /*!< Latitude in ? @todo*/
                          F64 longitude, /*!< Longitude in ? @todo*/
                          U16 altitude,  /*!< Altitude in meters*/
                          U8 satellite   /*!< Satellite count*/
    );

    PRIVATE :

        // ----------------------------------------------------------------------
        // Command handler implementations
        // ----------------------------------------------------------------------

        //! Implementation for PiCam command handler
        //! Take picture
        void
        PiCam_TakePicture_cmdHandler(
            const FwOpcodeType opCode, /*!< The opcode*/
            const U32 cmdSeq           /*!< The command sequence number*/
        );

    U32 pictureCnt;
};

}  // end namespace App

#endif
