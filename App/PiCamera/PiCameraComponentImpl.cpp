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
    ) : PiCameraComponentBase(compName), nbPicture(0) ,width(320),
     height(240), indexSSDV(0), timeInterval(18), timeCpt(0), sendingPicture(0), pictureId(-1)
     ,fileSize(0), currentTime(0), nbPacket(0), canSend(false), latitude(0), longitude(0),
     flexExterTemp(0), flexInterTemp(0), altitudeGps(0), altitudeBaro(0), satellite(0), temperature(0),
     pressure(0)
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
    ","<<"Temperature"<<","<< "Pressure"<<","<< "Longitude" <<","<< "Latitude" <<
    ","<< "FlexInternTemp" <<","<< "FlexExternTemp"  "\n";
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
    //log_ACTIVITY_LO_PiCam_PositionUpdate();
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
    //this->log_ACTIVITY_LO_PiCam_BarometerDataUpdate(temperature,pressure,altitude);
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
      if(timeInterval == 0){
        return;
      }
      if(timeCpt < timeInterval){
          timeCpt++;
          return;
      }

      currentTime = getTime().getSeconds();
      writeLastPictureTaken();
      if(takePicture(BASE_WIDTH,BASE_HEIGHT,false) && takePicture(width,height,true) ){
          ++nbPicture;
          tlmWrite_PiCam_PictureCnt(nbPicture);
          log_ACTIVITY_LO_PiCam_PictureTaken();
          timeCpt=1;
          return;
      }
      log_WARNING_LO_PiCam_PictureError(0);
  }

      void PiCameraComponentImpl::SendFrame_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 frame
      ){
        if(pictureId ==-1 || !canSend){
          return;
        }
        sendAvailableFrame();
      }

    void PiCameraComponentImpl::tempProbeInternal_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I16 degree /*!< The call order*/
      ){
          this->flexInterTemp = degree;
      }
      
    void PiCameraComponentImpl::tempProbeExternal_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I16 degree /*!< The call order*/
      ){
        this->flexExterTemp = degree;
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
    currentTime = getTime().getSeconds();
    writeLastPictureTaken();
    if(takePicture(BASE_WIDTH,BASE_HEIGHT,false) && takePicture(width,height,true) ){
      ++nbPicture;
      tlmWrite_PiCam_PictureCnt(nbPicture);
      log_ACTIVITY_LO_PiCam_PictureTaken();
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
      return;
    }
    log_WARNING_LO_PiCam_PictureError(0);
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);

  }

   void PiCameraComponentImpl::PiCam_LoadLast_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      ){

        if(nbPicture == 0 || pictureId == nbPicture || currentTime == 0){
          this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
          return;
        }

          pictureId = nbPicture;
          sendingPicture = currentTime;
          std::ostringstream osData;
          osData << DATA_DIRECTORY << "data.bin";
          std::ofstream outFileData (osData.str(), std::ios::out | std::ios::binary);
          outFileData.write((char*)&sendingPicture,sizeof(sendingPicture));
          outFileData.write((char*)&pictureId,sizeof(pictureId));
          outFileData.close();

          loadPicture(true);
        
        
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
          I16 frameId
      ){
          if(frameId > (I32)nbPacket -1){
            printf("dedewdewdewd\n");
          }
         if(pictureId == -1 || frameId < -1 || frameId > nbPacket-1){
           printf("picturedi: %u, frameId: %hd, nbpacket: %d\n",pictureId,frameId,nbPacket-1);
          this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
          return;
        }
        if(frameId == -1){
          delete frameSend;
          frameSend = new bool[nbPacket]{false};
        }else{
            frameSend[frameId] = false;
        }
         
        this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
      }

     void PiCameraComponentImpl::PiCam_StopSending_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      ){
        this->canSend = false;
        this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
        
      }
     void PiCameraComponentImpl::PiCam_StartSending_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          I16 startFrame
      ){
        if(pictureId ==-1 || startFrame < -1 || startFrame > nbPacket-1){
          this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
          return;
        }
        canSend = true;
        if(startFrame !=-1){
          for(U32 i = 0; i<startFrame;i++){
              frameSend[i] = true;
          }
          for(U32 i = startFrame; i<nbPacket; i++){
              frameSend[i] = false;
          }

        }
        sendAvailableFrame();
        this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
      }

  bool PiCameraComponentImpl::takePicture(U32 width, U32 height, bool ground){
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
    
    //capture
    Camera.grab();
    
    //allocate memory
    unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    printf("size %d \n",(int)Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ));
    
    //extract the image in rgb format
    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image

    if(ground){
      manageJpg(data, width, height);
    }
    else{
    managePpm(Camera,data);
    managePng(data, width, height);
    manageTelemetry();
    }
    delete data;
    return true;
  }    

  void PiCameraComponentImpl::manageTelemetry(){
    std::ostringstream osTelemetry;
    osTelemetry << TELEMETRY_DIRECTORY << "telemetry.csv";
    std::ofstream outFileTelemetry (osTelemetry.str(),std::ios::app );

    outFileTelemetry << nbPicture <<","<<currentTime <<"," << altitudeGps <<","<< altitudeBaro << 
    ","<<temperature<<","<< pressure<<","<< longitude<<","<< latitude << 
    ","<< flexInterTemp<<","<< flexExterTemp << "\n";

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

  void PiCameraComponentImpl::managePng(unsigned char* data, U32 width, U32 height){
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

  void PiCameraComponentImpl::manageJpg(unsigned char* data, U32 width, U32 height){
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

    TooJpeg::writeJpeg(myOutput, data, width, height, isRGB, quality, downsample, comment);
    PiCameraComponentImpl::jpgFile.close();
    system(osPictureSsdv.str().c_str());
  }

    
  void PiCameraComponentImpl::myOutput(unsigned char byte){
      PiCameraComponentImpl::jpgFile << byte;
    }

  void PiCameraComponentImpl::loadPicture(bool isTrue){
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
      if(isTrue){
        for(int i = 0; i<nbPacket; i++){
          frameSend[i] = true;
        }
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

      loadPicture(false);
      loadLastPictureTaken();
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
  void PiCameraComponentImpl::loadLastPictureTaken(){
      std::ifstream indata; // indata is like cin
      std::ostringstream osData;
      osData << DATA_DIRECTORY << "dataPicture.bin";
      indata.open(osData.str(), std::ios::in | std::ios::binary); // opens the file
      if(!indata){
        return;
      }
      indata.read((char*)&currentTime,sizeof(currentTime));
      indata.close();
    }
  void PiCameraComponentImpl::writeLastPictureTaken(){
    
      std::ostringstream osData;
      osData << DATA_DIRECTORY << "dataPicture.bin";
      std::ofstream outFileData (osData.str(), std::ios::out | std::ios::binary);
      outFileData.write((char*)&currentTime,sizeof(currentTime));
      outFileData.close();
  }
  void PiCameraComponentImpl::sendAvailableFrame(){
    for(U32 i = 0; i< nbPacket;i++){
          if(!frameSend[i]){
            printf("Send frame %u/%u of picture %u\n", i, nbPacket, pictureId);
            this->sendFrame(i);
            frameSend[i] = true;
            return;
          }
       }
  }


} // end namespace App