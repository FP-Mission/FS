// ======================================================================
// \title  PiCameraComponentImpl.cpp
// \author root
// \brief  cpp file for PiCamera component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/PiCamera/PiCameraComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Os/FileSystem.hpp"
#include "App/Config/PiCameraConfig.hpp"

#include <fstream>
#include <iostream>
#include <raspicam/raspicam.h>
#include <png++/png.hpp>
#include <unistd.h>
#include <sstream>


namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  PiCameraComponentImpl ::
    PiCameraComponentImpl(
        const char *const compName
    ) : PiCameraComponentBase(compName), nbPicture(0)
  {
    Os::FileSystem::Status status = Os::FileSystem::createDirectory(BASE_DIRECTORY);
    if(status == Os::FileSystem::Status::OP_OK){
      Os::FileSystem::createDirectory(TELEMETRY_DIRECTORY);
      Os::FileSystem::createDirectory(PICTURE_DIRECTORY);
      Os::FileSystem::createDirectory(PPM_DIRECTORY);
      Os::FileSystem::createDirectory(PNG_DIRECTORY);


    std::ostringstream osTelemetry;
    osTelemetry << TELEMETRY_DIRECTORY << "telemetry.csv";
    std::ofstream outFileTelemetry (osTelemetry.str());
    outFileTelemetry<< "Timecode" <<","<< "AltitudeGPS" <<","<< "AltitudeBaro" << 
    ","<<"Temperature"<<","<< "Pressure"<<","<< "Longitude" <<","<< "Latitude" << "\n";
    outFileTelemetry.close();
    }
  }

  void PiCameraComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    PiCameraComponentBase::init(queueDepth, instance);
  }

  PiCameraComponentImpl ::
    ~PiCameraComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void PiCameraComponentImpl ::
    PingIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    PingOut_out(0, key);
  }

  void PiCameraComponentImpl ::
    position_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Time time,
        F64 latitude,
        F64 longitude,
        U16 altitude,
        U8 satellite
    )
  {
    this->latitude = latitude;
    this->longitude = longitude;
    this->altitudeGps = altitude;
    this->satellite = satellite; 
  }

  void PiCameraComponentImpl ::
    barometerDataIn_handler(
        const NATIVE_INT_TYPE portNum,
        U16 altitude,
        F32 pressure,
        F32 temperature
    )
  {
    this->altitudeBaro = altitude;
    this->pressure = pressure;
    this->temperature = temperature;
    this->log_ACTIVITY_LO_PiCam_BarometerDataUpdate(temperature,pressure,altitude);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void PiCameraComponentImpl ::
    PiCam_TakePicture_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    std::ostringstream osPicture;

    raspicam::RaspiCam Camera; //Camera object
    Camera.setWidth ( 1920 );
    Camera.setHeight ( 1080 );
    png::image< png::rgb_pixel > image(1920, 1080);
    //Open camera
    std::cout<<"Opening Camera..."<<std::endl;
    if ( !Camera.open()) {std::cerr<<"Error opening camera"<<std::endl;}
    //wait a while until camera stabilizes
    std::cout<<"Sleeping for 3 secs"<<std::endl;
    sleep(3);
    currentTime = getTime().getSeconds();
    //capture
    Camera.grab();
    //allocate memory
    unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    printf("size %d \n",(int)Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ));
    //extract the image in rgb format
    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image
    int index = 0;
    for (size_t y = 0; y < image.get_height(); ++y)
    {
        for (size_t x = 0; x < image.get_width(); ++x)
        {
            image[y][x] = png::rgb_pixel(data[index], data[index+1],data[index+2] );
            // non-checking equivalent of image.set_pixel(x, y, ...);
            index += 3;
        }
    }
    osPicture << PNG_DIRECTORY << currentTime <<".png";
    image.write(osPicture.str());
    //save
    osPicture.str("");
    osPicture.clear();
    osPicture << PPM_DIRECTORY << currentTime <<".ppm";
    std::ofstream outFilePpm ( osPicture.str() ,std::ios::binary );
    
    outFilePpm<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";
    outFilePpm.write ( ( char* ) data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    //free resrources
    outFilePpm.close();

    delete data;
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void PiCameraComponentImpl::manageTelemetry(){
    std::ostringstream osTelemetry;
    osTelemetry << TELEMETRY_DIRECTORY << "telemetry.csv";
    std::ofstream outFileTelemetry (osTelemetry.str(),std::ios::app );

    outFileTelemetry << currentTime <<"," <<altitudeGps <<","<< altitudeBaro << 
    ","<<temperature<<","<< pressure<<","<< longitude<<","<< latitude << "\n";

    outFileTelemetry.close();
  }

} // end namespace App