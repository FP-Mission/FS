// ======================================================================
// \title  PiCameraComponentImpl.hpp
// \author root
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
#include "App/Config/PiCameraConfig.hpp"

#include <raspicam/raspicam.h>
#include <fstream>

namespace App {

  class PiCameraComponentImpl :
    public PiCameraComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object PiCamera
      //!
      PiCameraComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object PiCamera
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object PiCamera
      //!
      ~PiCameraComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for PingIn
      //!
      void PingIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Handler implementation for position
      //!
      void position_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time time, /*!< Measure time*/
          F64 latitude, /*!< Latitude in ? @todo*/
          F64 longitude, /*!< Longitude in ? @todo*/
          U16 altitude, /*!< Altitude in meters*/
          U8 satellite /*!< Satellite count*/
      );

      //! Handler implementation for barometerDataIn
      //!
      void barometerDataIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U16 altitude, /*!< Altitude value*/
          F32 pressure, /*!< Pressure value*/
          F32 temperature /*!< Temperature value*/
      );

      //! Handler implementation for SizeIn
     //!
      void SizeIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 width, /*!< wisth value*/
          U32 height /*!< height value*/
      );

      //! Handler implementation for Schedin
      //!
      void Schedin_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for PiCam_TakePicture command handler
      //! Take picture
      void PiCam_TakePicture_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      void PiCam_SetTimeInterval_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const U8 timeInterval /*!< The command sequence number*/
      );

      //! Implementation for PiCam_SetSize command handler
      //! Take picture
      void PiCam_SetSize_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 width,
          U32 height
      );

      bool takePicture();
      void manageTelemetry();
      void managePpm(raspicam::RaspiCam &camera ,unsigned char* data);
      void managePng(unsigned char* data);
      void manageJpg(unsigned char* data);

      static void myOutput(unsigned char byte);

      void getNumberOfLine(std::ostringstream& path);

      F32 temperature;
      F32 pressure;
      U16 altitudeBaro;

      F64 latitude;
      F64 longitude;
      U16 altitudeGps;
      U8 satellite;

      U32 nbPicture;
      U32 currentTime;

      U32 width;
      U32 height;

      static std::ofstream jpgFile;

      U8 indexSSDV;
      U8 timeInterval;
      U8 timeCpt;
    };

} // end namespace App

#endif