#include "LPS22.hpp"
#include "App/SenseHat/Config/LPS22HBConfig.hpp"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

namespace App{


  Lps22::Lps22() {
      init();
      startOneShot(); 
  }

  Lps22::~Lps22(void) {

  }

 void Lps22::cycle(){
   U8 buf[3];
   if((readByte(LPS_STATUS)&0x01)==0x01)   //a new pressure data is generated
        {
            buf[0]=readByte(LPS_PRESS_OUT_XL);
            buf[1]=readByte(LPS_PRESS_OUT_L);
            buf[2]=readByte(LPS_PRESS_OUT_H);
            pressureValue=(float)((buf[2]<<16)+(buf[1]<<8)+buf[0])/4096.0f;
        }
        if((readByte(LPS_STATUS)&0x02)==0x02)   // a new pressure data is generated
        {
            buf[0]=readByte(LPS_TEMP_OUT_L);
            buf[1]=readByte(LPS_TEMP_OUT_H);
            temperatureValue=(float)((buf[1]<<8)+buf[0])/100.0f;
        }
 }

  I8 Lps22::readByte(I32 reg){
    return wiringPiI2CReadReg8(fd, reg);
  }

  U16 Lps22::readU16(I32 reg){
      return wiringPiI2CReadReg16(fd, reg);
  }

  void Lps22::writeByte(I32 reg, I32 val){

      wiringPiI2CWriteReg8(fd, reg, val);
  }

  void Lps22::startOneShot(){
    U8 buf;
    buf=readU16(LPS_CTRL_REG2);
    buf|=0x01;                                         //ONE_SHOT Set 1
    writeByte(LPS_CTRL_REG2,buf);
  }

  void Lps22::reset(){
    U8 buf;
    buf=readU16(LPS_CTRL_REG2);
    buf|=0x04;                                         
    writeByte(LPS_CTRL_REG2,buf);                  //SWRESET Set 1
    while(buf)
    {
        buf=readU16(LPS_CTRL_REG2);
        buf&=0x04;
    }
  }

  U8 Lps22::init(){
    fd=wiringPiI2CSetup(LPS22HB_I2C_ADDRESS);
    if(readByte(LPS_WHO_AM_I)!=LPS_ID) return 0;    //Check device ID 
    reset();                                    //Wait for reset to complete
    writeByte(LPS_CTRL_REG1 ,   0x02);              //Low-pass filter disabled , output registers not updated until MSB and LSB have been read , Enable Block Data Update , Set Output Data Rate to 0 
    return 1;
  }


F32 Lps22::getTemperatureValue(){
  return this->temperatureValue;
}

F32 Lps22::getPressureValue(){
  return this->pressureValue;
}


}