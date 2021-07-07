// ======================================================================
// \title  PiCamera/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for PiCamera component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include "GTestBase.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  PiCameraGTestBase ::
    PiCameraGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
        PiCameraTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  PiCameraGTestBase ::
    ~PiCameraGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Commands
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertCmdResponse_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ((unsigned long) size, this->cmdResponseHistory->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of command response history\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->cmdResponseHistory->size() << "\n";
  }

  void PiCameraGTestBase ::
    assertCmdResponse(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
    const
  {
    ASSERT_LT(__index, this->cmdResponseHistory->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into command response history\n"
      << "  Expected: Less than size of command response history ("
      << this->cmdResponseHistory->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const CmdResponse& e = this->cmdResponseHistory->at(__index);
    ASSERT_EQ(opCode, e.opCode)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Opcode at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << opCode << "\n"
      << "  Actual:   " << e.opCode << "\n";
    ASSERT_EQ(cmdSeq, e.cmdSeq)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Command sequence number at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << cmdSeq << "\n"
      << "  Actual:   " << e.cmdSeq << "\n";
    ASSERT_EQ(response, e.response)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Command response at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << response << "\n"
      << "  Actual:   " << e.response << "\n";
  }

  // ----------------------------------------------------------------------
  // Telemetry
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertTlm_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->tlmSize)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all telemetry histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmSize << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: PiCam_PictureCnt
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertTlm_PiCam_PictureCnt_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_PiCam_PictureCnt->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel PiCam_PictureCnt\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_PiCam_PictureCnt->size() << "\n";
  }

  void PiCameraGTestBase ::
    assertTlm_PiCam_PictureCnt(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U8& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_PiCam_PictureCnt->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel PiCam_PictureCnt\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_PiCam_PictureCnt->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_PiCam_PictureCnt& e =
      this->tlmHistory_PiCam_PictureCnt->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel PiCam_PictureCnt\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: PiCam_PictureSize
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertTlm_PiCam_PictureSize_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_PiCam_PictureSize->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel PiCam_PictureSize\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_PiCam_PictureSize->size() << "\n";
  }

  void PiCameraGTestBase ::
    assertTlm_PiCam_PictureSize(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const App::PictureSize& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_PiCam_PictureSize->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel PiCam_PictureSize\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_PiCam_PictureSize->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_PiCam_PictureSize& e =
      this->tlmHistory_PiCam_PictureSize->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel PiCam_PictureSize\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: PiCam_Timeinterval
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertTlm_PiCam_Timeinterval_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_PiCam_Timeinterval->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel PiCam_Timeinterval\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_PiCam_Timeinterval->size() << "\n";
  }

  void PiCameraGTestBase ::
    assertTlm_PiCam_Timeinterval(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U8& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_PiCam_Timeinterval->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel PiCam_Timeinterval\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_PiCam_Timeinterval->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_PiCam_Timeinterval& e =
      this->tlmHistory_PiCam_Timeinterval->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel PiCam_Timeinterval\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertEvents_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all event histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_PictureTaken
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertEvents_PiCam_PictureTaken_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_PiCam_PictureTaken)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event PiCam_PictureTaken\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_PiCam_PictureTaken << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_PositionUpdate
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertEvents_PiCam_PositionUpdate_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_PiCam_PositionUpdate)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event PiCam_PositionUpdate\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_PiCam_PositionUpdate << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_BarometerDataUpdate
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertEvents_PiCam_BarometerDataUpdate_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_PiCam_BarometerDataUpdate->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event PiCam_BarometerDataUpdate\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_PiCam_BarometerDataUpdate->size() << "\n";
  }

  void PiCameraGTestBase ::
    assertEvents_PiCam_BarometerDataUpdate(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const F32 temp,
        const F32 pressure,
        const U16 altitude
    ) const
  {
    ASSERT_GT(this->eventHistory_PiCam_BarometerDataUpdate->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event PiCam_BarometerDataUpdate\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_PiCam_BarometerDataUpdate->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_PiCam_BarometerDataUpdate& e =
      this->eventHistory_PiCam_BarometerDataUpdate->at(__index);
    ASSERT_EQ(temp, e.temp)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument temp at index "
      << __index
      << " in history of event PiCam_BarometerDataUpdate\n"
      << "  Expected: " << temp << "\n"
      << "  Actual:   " << e.temp << "\n";
    ASSERT_EQ(pressure, e.pressure)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument pressure at index "
      << __index
      << " in history of event PiCam_BarometerDataUpdate\n"
      << "  Expected: " << pressure << "\n"
      << "  Actual:   " << e.pressure << "\n";
    ASSERT_EQ(altitude, e.altitude)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument altitude at index "
      << __index
      << " in history of event PiCam_BarometerDataUpdate\n"
      << "  Expected: " << altitude << "\n"
      << "  Actual:   " << e.altitude << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_PictureError
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertEvents_PiCam_PictureError_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_PiCam_PictureError->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event PiCam_PictureError\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_PiCam_PictureError->size() << "\n";
  }

  void PiCameraGTestBase ::
    assertEvents_PiCam_PictureError(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32 code
    ) const
  {
    ASSERT_GT(this->eventHistory_PiCam_PictureError->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event PiCam_PictureError\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_PiCam_PictureError->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_PiCam_PictureError& e =
      this->eventHistory_PiCam_PictureError->at(__index);
    ASSERT_EQ(code, e.code)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument code at index "
      << __index
      << " in history of event PiCam_PictureError\n"
      << "  Expected: " << code << "\n"
      << "  Actual:   " << e.code << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_SetTimeInterval
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertEvents_PiCam_SetTimeInterval_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_PiCam_SetTimeInterval->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event PiCam_SetTimeInterval\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_PiCam_SetTimeInterval->size() << "\n";
  }

  void PiCameraGTestBase ::
    assertEvents_PiCam_SetTimeInterval(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U8 timeInterval
    ) const
  {
    ASSERT_GT(this->eventHistory_PiCam_SetTimeInterval->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event PiCam_SetTimeInterval\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_PiCam_SetTimeInterval->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_PiCam_SetTimeInterval& e =
      this->eventHistory_PiCam_SetTimeInterval->at(__index);
    ASSERT_EQ(timeInterval, e.timeInterval)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument timeInterval at index "
      << __index
      << " in history of event PiCam_SetTimeInterval\n"
      << "  Expected: " << timeInterval << "\n"
      << "  Actual:   " << e.timeInterval << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: PiCam_SetPictureSize
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertEvents_PiCam_SetPictureSize_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_PiCam_SetPictureSize->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event PiCam_SetPictureSize\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_PiCam_SetPictureSize->size() << "\n";
  }

  void PiCameraGTestBase ::
    assertEvents_PiCam_SetPictureSize(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32 width,
        const U32 height
    ) const
  {
    ASSERT_GT(this->eventHistory_PiCam_SetPictureSize->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event PiCam_SetPictureSize\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_PiCam_SetPictureSize->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_PiCam_SetPictureSize& e =
      this->eventHistory_PiCam_SetPictureSize->at(__index);
    ASSERT_EQ(width, e.width)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument width at index "
      << __index
      << " in history of event PiCam_SetPictureSize\n"
      << "  Expected: " << width << "\n"
      << "  Actual:   " << e.width << "\n";
    ASSERT_EQ(height, e.height)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument height at index "
      << __index
      << " in history of event PiCam_SetPictureSize\n"
      << "  Expected: " << height << "\n"
      << "  Actual:   " << e.height << "\n";
  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assertFromPortHistory_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all from port histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: PingOut
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assert_from_PingOut_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_PingOut->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_PingOut\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_PingOut->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: PictureOut
  // ----------------------------------------------------------------------

  void PiCameraGTestBase ::
    assert_from_PictureOut_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_PictureOut->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_PictureOut\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_PictureOut->size() << "\n";
  }

} // end namespace App
