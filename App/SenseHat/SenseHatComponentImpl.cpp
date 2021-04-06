// ======================================================================
// \title  SenseHatComponentImpl.cpp
// \author root
// \brief  cpp file for SenseHat component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <App/SenseHat/SenseHatComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Buffer/Buffer.hpp>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <math.h>
#include "SHTC3/SHTC3.h"
#include <unistd.h>

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  SenseHatComponentImpl ::
    SenseHatComponentImpl(
        const char *const compName
    ) : SenseHatComponentBase(compName)
  {

  }

  void SenseHatComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    SenseHatComponentBase::init(queueDepth, instance);
  }

  SenseHatComponentImpl ::
    ~SenseHatComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void SenseHatComponentImpl ::
    Schedin_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    //log_ACTIVITY_LO_MS_TM_RECV_TEMP(12.6f);
    //tlmWrite_SENSE_LAST_TM_DATA(12.8f);
  }

  void SenseHatComponentImpl ::
    PingIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {

      PingOut_out(portNum,key);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void SenseHatComponentImpl ::
    MS_GET_TM_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    float TH_Value,RH_Value;
    fd=wiringPiI2CSetup(SHTC3_I2C_ADDRESS);
    SHTC3_WriteCommand(SHTC3_Software_RES);                 // Write reset command
    delayMicroseconds(300);   
    SHTC3_WriteCommand(SHTC3_WakeUp);                  // write wake_up command  
    delayMicroseconds(300); 

        unsigned short TH_DATA,RH_DATA;
    char buf[3];
   SHTC3_WriteCommand(SHTC3_NM_CD_ReadTH);                 //Read temperature first,clock streching disabled (polling)
    delay(20);
    read(fd, buf, 3);  
    TH_DATA=(buf[0]<<8|buf[1]);

    TH_Value=175 * (float)TH_DATA / 65536.0f - 45.0f; 
    printf("temp : %6.2f°C \n",TH_Value);
    log_ACTIVITY_LO_MS_TM_RECV_TEMP(TH_Value);
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
    
  }

    void SenseHatComponentImpl::SHTC3_WriteCommand(unsigned short cmd)
    {   
      char buf[] = { (cmd>>8) ,cmd};
      wiringPiI2CWriteReg8(fd,buf[0],buf[1]);          
                                                    //1:error 0:No error
    }

} // end namespace App
