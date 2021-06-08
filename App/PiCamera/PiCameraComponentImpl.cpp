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
#include <Fw/Com/ComPacket.hpp>


#include "toojpeg.h"
#include <iostream>
#include <png++/png.hpp>
#include <unistd.h>
#include <sstream>


namespace App {

  std::ofstream PiCameraComponentImpl::jpgFile;
  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  PiCameraComponentImpl ::
    PiCameraComponentImpl(
        const char *const compName
    ) : PiCameraComponentBase(compName), nbPicture(0) ,width(BASE_WIDTH),
     height(BASE_HEIGHT), indexSSDV(0), timeInterval(6), timeCpt(0), sendingPicture(0), pictureId(0)
     ,fileSize(0), currentTime(0), nbPacket(-1)
  {
    std::ostringstream osTelemetry;
    osTelemetry << TELEMETRY_DIRECTORY << "telemetry.csv";
    Os::FileSystem::Status status = Os::FileSystem::createDirectory(BASE_DIRECTORY);

    if(status == Os::FileSystem::Status::OP_OK){
      Os::FileSystem::createDirectory(TELEMETRY_DIRECTORY);
      Os::FileSystem::createDirectory(PICTURE_DIRECTORY);
      Os::FileSystem::createDirectory(PPM_DIRECTORY);
      Os::FileSystem::createDirectory(PNG_DIRECTORY);
      Os::FileSystem::createDirectory(JPG_DIRECTORY);
      Os::FileSystem::createDirectory(BIN_DIRECTORY);
      Os::FileSystem::createDirectory(DATA_DIRECTORY);


    std::ofstream outFileTelemetry (osTelemetry.str());
    outFileTelemetry<< "id" <<","<<"Timecode" <<","<< "AltitudeGPS" <<","<< "AltitudeBaro" << 
    ","<<"Temperature"<<","<< "Pressure"<<","<< "Longitude" <<","<< "Latitude" << "\n";
    outFileTelemetry.close();
    }
    getNumberOfLine(osTelemetry);
    loadData();
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
    log_ACTIVITY_LO_PiCam_PositionUpdate();
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

  void PiCameraComponentImpl ::
    Schedin_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
      tlmWrite_PiCam_Timeinterval(this->timeInterval);
      PictureSize pictureSize(this->width,this->height);
      tlmWrite_PiCam_PictureSize(pictureSize);
      if(timeInterval == 0){
        return;
      }
      if(timeCpt < timeInterval){
          timeCpt++;
          return;
      }
      bool sucessPicture = takePicture();
      if (sucessPicture){
          log_ACTIVITY_LO_PiCam_PictureTaken();
          //PictureOut_out(0,currentTime);
          timeCpt=1;
          return;
      }
      log_WARNING_LO_PiCam_PictureError(0);
  }

      void PiCameraComponentImpl::SendFrame_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 frame
      ){
          if(pictureId ==-1){
          return;
        }
        for(U32 i = 0; i< nbPacket;i++){
          if(!frameSend[i]){
            this->sendFrame(i);
            frameSend[i] = true;
          }
       }
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
    bool sucessPicture = takePicture();
    if(sucessPicture){
      log_ACTIVITY_LO_PiCam_PictureTaken();
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
      //PictureOut_out(0,currentTime);
      return;
    }
    log_WARNING_LO_PiCam_PictureError(0);
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);

  }

   void PiCameraComponentImpl::PiCam_SendLast_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      ){
        if(nbPicture == 0 || pictureId == nbPicture){
          this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
          return;
        }
        if(currentTime != 0){
        pictureId = nbPicture;
        sendingPicture = currentTime;
        std::ostringstream osData;
        osData << DATA_DIRECTORY << "data.bin";
        std::ofstream outFileData (osData.str(), std::ios::out | std::ios::binary);
        outFileData.write((char*)&sendingPicture,sizeof(sendingPicture));
        outFileData.write((char*)&pictureId,sizeof(pictureId));
        outFileData.close();

        loadPicture();
        }

        for(U32 i = 0; i< nbPacket; i++){
            this->sendFrame(i);
        }

        
        
        this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
      }

  void PiCameraComponentImpl::PiCam_SetTimeInterval_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const U8 timeInterval /*!< The command sequence number*/
      ){
        this->timeInterval = timeInterval;
        tlmWrite_PiCam_Timeinterval(timeInterval);
        log_ACTIVITY_LO_PiCam_SetTimeInterval(timeInterval);
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
        PictureSize pictureSize(this->width,this->height);
        tlmWrite_PiCam_PictureSize(pictureSize);
        log_ACTIVITY_LO_PiCam_SetPictureSize(width,height);
        this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
      }

      void PiCameraComponentImpl::PiCam_SendFrame_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U16 frameId
      ){
         if(pictureId == -1 || frameId < 0 || frameId > nbPacket){
          this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
          return;
        }
         frameSend[frameId] = false;
          
          this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
      }

  bool PiCameraComponentImpl::takePicture(){
    raspicam::RaspiCam Camera; //Camera object
    Camera.setWidth(width);
    Camera.setHeight(height);
    //Open camera
    std::cout<<"Opening Camera..."<<std::endl;
    if ( !Camera.open()) {
      std::cerr<<"Error opening camera"<<std::endl;
      return false;
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

    ++nbPicture;
    managePpm(Camera,data);
    managePng(data);
    manageJpg(data);
    manageTelemetry();
   
    tlmWrite_PiCam_PictureCnt(nbPicture);

    delete data;
    return true;
  }    

  void PiCameraComponentImpl::manageTelemetry(){
    std::ostringstream osTelemetry;
    osTelemetry << TELEMETRY_DIRECTORY << "telemetry.csv";
    std::ofstream outFileTelemetry (osTelemetry.str(),std::ios::app );

    outFileTelemetry << nbPicture <<","<<currentTime <<"," <<altitudeGps <<","<< altitudeBaro << 
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

  void PiCameraComponentImpl::manageJpg(unsigned char* data){
    std::ostringstream osPicture;
    std::ostringstream osPictureSsdv;
    osPictureSsdv << "ssdv -e -c BALL -i "<< (U32)indexSSDV <<" "<< JPG_DIRECTORY << currentTime <<".jpg " << BIN_DIRECTORY <<currentTime<<".bin";
    osPicture << JPG_DIRECTORY << currentTime <<".jpg";

    ++indexSSDV;

    PiCameraComponentImpl::jpgFile.open(osPicture.str() ,std::ios_base::out | std::ios_base::binary);
    const bool isRGB      = true;  // true = RGB image, else false = grayscale
    const auto quality    = 90;    // compression quality: 0 = worst, 100 = best, 80 to 90 are most often used
    const bool downsample = false; // false = save as YCbCr444 JPEG (better quality), true = YCbCr420 (smaller file)
    const char* comment = "image"; // arbitrary JPEG comment

    TooJpeg::writeJpeg(myOutput, data, 160, 120, isRGB, quality, downsample, comment);
    PiCameraComponentImpl::jpgFile.close();
    system(osPictureSsdv.str().c_str());
  }

    
  void PiCameraComponentImpl::myOutput(unsigned char byte){
      PiCameraComponentImpl::jpgFile << byte;
    }

  void PiCameraComponentImpl::loadPicture(){
    delete binaryData;
    delete frameSend;
      std::ostringstream osPictureSsdv;
      osPictureSsdv << BIN_DIRECTORY << sendingPicture <<".bin";
      std::ifstream in(osPictureSsdv.str().c_str(),std::ios::binary | std::ios::ate);
      if(!in){
        return;
      }
      fileSize = in.tellg();
      in.seekg (0, std::ios::beg);
      binaryData = new U8[fileSize];
      nbPacket = fileSize/SIZE_PACKET;
      frameSend = new bool[nbPacket]{ false};
      for(U32 i = 0; i< nbPacket;i++){
        printf("%d\n",frameSend[i]);
      }
      char* dataChar = reinterpret_cast<char*>(binaryData);
      in.read(dataChar ,fileSize);

      in.close();
  }

  void PiCameraComponentImpl::loadData(){
      if(nbPicture == 0){
        return;
      }
      std::ifstream indata; // indata is like cin
      std::ostringstream osData;
      osData << DATA_DIRECTORY << "data.bin";
      indata.open(osData.str(), std::ios::in | std::ios::binary); // opens the file
      if(!indata){
        return;
      }
      indata.read((char*)&sendingPicture,sizeof(sendingPicture));
      indata.read((char*)&pictureId,sizeof(pictureId));
      indata.close();

      loadPicture();
  }
  void PiCameraComponentImpl::sendFrame(U16 frameId){
        m_picturePacket.setData(binaryData, frameId, SIZE_PACKET, fileSize);
        m_picturePacket.setFrameId(frameId);
        m_picturePacket.setPictureId(pictureId);
        m_comBuffer.resetSer();
        Fw::SerializeStatus stat = this->m_picturePacket.serialize(this->m_comBuffer);
        FW_ASSERT(Fw::FW_SERIALIZE_OK == stat,static_cast<NATIVE_INT_TYPE>(stat));
        this->PictureOut_out(0,this->m_comBuffer,0);
  }

} // end namespace App