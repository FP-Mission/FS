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
#include <Fw/Tlm/PicturePacket.hpp>

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

    void SendFrame_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 frame /*!< The call order*/
      );
    void tempProbeInternal_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I16 degree /*!< The call order*/
      );
    void tempProbeExternal_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I16 degree /*!< The call order*/
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

     void PiCam_LoadLast_cmdHandler(
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

      void PiCam_SendFrame_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U16 wframeIdidth
      );

    void PiCam_CanSend_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 canSend,
          U16 startFrame
      );

     void PiCam_StartSending_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      bool takePicture(U32 width, U32 height, bool ground);
      void manageTelemetry();
      void managePpm(raspicam::RaspiCam &camera ,unsigned char* data);
      void managePng(unsigned char* data, U32 width, U32 height);
      void manageJpg(unsigned char* data, U32 width, U32 height);
      void sendAvailableFrame();

      static void myOutput(unsigned char byte);

      void getNumberOfLine(std::ostringstream& path);

      void loadPicture(bool);
      void loadData();
      void loadLastPictureTaken();
      void writeLastPictureTaken();
      void sendFrame(U16 frameId);     
     
      F32 temperature;
      F32 pressure;
      U16 altitudeBaro;

      F64 latitude;
      F64 longitude;
      U16 altitudeGps;
      U8 satellite;

      I16 flexInterTemp;
      I16 flexExterTemp;

      U32 nbPicture;
      U32 currentTime;

      U32 width;
      U32 height;

      static std::ofstream jpgFile;

      U8 indexSSDV;
      U8 timeInterval;
      U8 timeCpt;

      U32 sendingPicture;
      U32 pictureId;
      U32 fileSize;
      U32 nbPacket;

     Fw::ComBuffer m_comBuffer;
     Fw::PicturePacket m_picturePacket;
     U8* binaryData;
     bool* frameSend;
     bool canSend;

    };

} // end namespace App

#endif