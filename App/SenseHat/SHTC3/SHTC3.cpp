#include "SHTC3.hpp"
#include "App/SenseHat/Config/SHTC3Config.hpp"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

namespace App{


  Shtc3::Shtc3() {
    wiringPiSetup();
    fd=wiringPiI2CSetup(SHTC3_I2C_ADDRESS);
    softReset();
  }

  Shtc3::~Shtc3(void) {

  }

 void Shtc3::cycle(){
    wakeUp();
    readData();
    sleep();
 }

void Shtc3::writeCommand(U16 cmd){
    I8 buf[] = { (I8)(cmd>>8) ,(I8)cmd};
    wiringPiI2CWriteReg8(fd,buf[0],buf[1]);    
}

void Shtc3::wakeUp(){
    writeCommand(SHTC3_WakeUp);                  // write wake_up command  
    delayMicroseconds(300);  
}

void Shtc3::sleep(){
    writeCommand(SHTC3_Sleep);   
}

void Shtc3::softReset(){
    writeCommand(SHTC3_Software_RES);                 // Write reset command
    delayMicroseconds(300); 
}

void Shtc3::readData(){
    U16 TH_DATA = 0, RH_DATA=0;
    I8 buf[3];
    writeCommand(SHTC3_NM_CD_ReadTH);                 //Read temperature first,clock streching disabled (polling)
    delay(20);
    read(fd, buf, 3);

    I8 checksum=buf[2];
    if(!checkCrc(buf,2,checksum))
        TH_DATA=(buf[0]<<8|buf[1]);

    writeCommand(SHTC3_NM_CD_ReadRH);                 //Read temperature first,clock streching disabled (polling)
    delay(20);
    read(fd, buf, 3);

    checksum=buf[2];
    if(!checkCrc(buf,2,checksum))
        RH_DATA=(buf[0]<<8|buf[1]);
    
    // printf("TH data %d, ",TH_DATA);
    // printf("RH data %d\n",RH_DATA);

    temperatureValue = 175 * (float)TH_DATA / 65536.0f - 45.0f;       //Calculate temperature value
    humidityValue =100 * (float)RH_DATA / 65536.0f;              //Calculate humidity value  
    
}

F32 Shtc3::getTemperatureValue(){
  return this->temperatureValue;
}

F32 Shtc3::getHumidityValue(){
  return this->humidityValue;
}


I8 Shtc3::checkCrc(I8 data[],U8 len,U8 checksum)
  {
  unsigned char bit;        // bit mask
  unsigned char crc = 0xFF; // calculated checksum
  unsigned char byteCtr;    // byte counter
  // calculates 8-Bit checksum with given polynomial
  for(byteCtr = 0; byteCtr < len; byteCtr++) {
    crc ^= (data[byteCtr]);
    for(bit = 8; bit > 0; --bit) {
      if(crc & 0x80) {
        crc = (crc << 1) ^ CRC_POLYNOMIAL;
      } else {
        crc = (crc << 1);
      }
    }
  }
  // verify checksum
  if(crc != checksum) {                 
    return 1;                       //Error
  } else {
    return 0;                       //No error
  }  
  }
}