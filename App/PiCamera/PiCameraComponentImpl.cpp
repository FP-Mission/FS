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
    ) : PiCameraComponentBase(compName), nbPicture(0) ,width(BASE_WIDTH), height(BASE_HEIGHT)
  {
    std::ostringstream osTelemetry;
    osTelemetry << TELEMETRY_DIRECTORY << "telemetry.csv";
    Os::FileSystem::Status status = Os::FileSystem::createDirectory(BASE_DIRECTORY);

    if(status == Os::FileSystem::Status::OP_OK){
      Os::FileSystem::createDirectory(TELEMETRY_DIRECTORY);
      Os::FileSystem::createDirectory(PICTURE_DIRECTORY);
      Os::FileSystem::createDirectory(PPM_DIRECTORY);
      Os::FileSystem::createDirectory(PNG_DIRECTORY);


    std::ofstream outFileTelemetry (osTelemetry.str());
    outFileTelemetry<< "Timecode" <<","<< "AltitudeGPS" <<","<< "AltitudeBaro" << 
    ","<<"Temperature"<<","<< "Pressure"<<","<< "Longitude" <<","<< "Latitude" << "\n";
    outFileTelemetry.close();
    }

    getNumberOfLine(osTelemetry);

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

    void PiCameraComponentImpl ::
    SizeIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 width,
        U32 height
    )
  {
    this->width=width;
    this->height=height;
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
    raspicam::RaspiCam Camera; //Camera object
    Camera.setWidth(width);
    Camera.setHeight(height);
    //Open camera
    std::cout<<"Opening Camera..."<<std::endl;
    if ( !Camera.open()) {
      std::cerr<<"Error opening camera"<<std::endl;
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
      return;
      }
      
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

    managePpm(Camera,data);
    managePng(data);
    manageTelemetry();
   
    ++nbPicture;
    tlmWrite_PiCam_PictureCnt(nbPicture);

    delete data;
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }
  void PiCameraComponentImpl ::
     PiCam_SetSize_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 width,
          U32 height
      ){
        this->width = width;
        this->height = height;
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

  void PiCameraComponentImpl::managePpm(raspicam::RaspiCam &camera ,unsigned char* data){
    std::ostringstream osPicture;
    osPicture << PPM_DIRECTORY << currentTime <<".ppm";
    std::ofstream outFilePpm ( osPicture.str() ,std::ios::binary );
    
    outFilePpm<<"P6\n"<<camera.getWidth() <<" "<<camera.getHeight() <<" 255\n";
    outFilePpm.write ( ( char* ) data, camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    //free resrources
    outFilePpm.close();
  }

  void PiCameraComponentImpl::managePng(unsigned char* data){
    std::ostringstream osPicture;
    png::image< png::rgb_pixel > image(width, height);

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
  }

  void  PiCameraComponentImpl::getNumberOfLine(std::ostringstream& path){
    std::ifstream f(path.str());
    std::string line;
    for (nbPicture = 0; std::getline(f, line); ++nbPicture);
    --nbPicture;
  }

} // end namespace App