// ======================================================================
// \title  MotionTracking/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for MotionTracking component Google Test harness base class
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

  MotionTrackingGTestBase ::
    MotionTrackingGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
        MotionTrackingTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  MotionTrackingGTestBase ::
    ~MotionTrackingGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Telemetry
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
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
  // Channel: MOTIONTRACKING_ANGLES
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
    assertTlm_MOTIONTRACKING_ANGLES_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_MOTIONTRACKING_ANGLES->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel MOTIONTRACKING_ANGLES\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_MOTIONTRACKING_ANGLES->size() << "\n";
  }

  void MotionTrackingGTestBase ::
    assertTlm_MOTIONTRACKING_ANGLES(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const App::AnglesTlm& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_MOTIONTRACKING_ANGLES->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel MOTIONTRACKING_ANGLES\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_MOTIONTRACKING_ANGLES->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_MOTIONTRACKING_ANGLES& e =
      this->tlmHistory_MOTIONTRACKING_ANGLES->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel MOTIONTRACKING_ANGLES\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: MOTIONTRACKING_GYRO
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
    assertTlm_MOTIONTRACKING_GYRO_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_MOTIONTRACKING_GYRO->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel MOTIONTRACKING_GYRO\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_MOTIONTRACKING_GYRO->size() << "\n";
  }

  void MotionTrackingGTestBase ::
    assertTlm_MOTIONTRACKING_GYRO(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const App::VectorTlm& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_MOTIONTRACKING_GYRO->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel MOTIONTRACKING_GYRO\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_MOTIONTRACKING_GYRO->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_MOTIONTRACKING_GYRO& e =
      this->tlmHistory_MOTIONTRACKING_GYRO->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel MOTIONTRACKING_GYRO\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: MOTIONTRACKING_ACCEL
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
    assertTlm_MOTIONTRACKING_ACCEL_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_MOTIONTRACKING_ACCEL->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel MOTIONTRACKING_ACCEL\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_MOTIONTRACKING_ACCEL->size() << "\n";
  }

  void MotionTrackingGTestBase ::
    assertTlm_MOTIONTRACKING_ACCEL(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const App::VectorTlm& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_MOTIONTRACKING_ACCEL->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel MOTIONTRACKING_ACCEL\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_MOTIONTRACKING_ACCEL->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_MOTIONTRACKING_ACCEL& e =
      this->tlmHistory_MOTIONTRACKING_ACCEL->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel MOTIONTRACKING_ACCEL\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: MOTIONTRACKING_MAGN
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
    assertTlm_MOTIONTRACKING_MAGN_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_MOTIONTRACKING_MAGN->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel MOTIONTRACKING_MAGN\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_MOTIONTRACKING_MAGN->size() << "\n";
  }

  void MotionTrackingGTestBase ::
    assertTlm_MOTIONTRACKING_MAGN(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const App::VectorTlm& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_MOTIONTRACKING_MAGN->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel MOTIONTRACKING_MAGN\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_MOTIONTRACKING_MAGN->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_MOTIONTRACKING_MAGN& e =
      this->tlmHistory_MOTIONTRACKING_MAGN->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel MOTIONTRACKING_MAGN\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
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
  // Event: MS_DATA
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
    assertEvents_MS_DATA_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_MS_DATA)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event MS_DATA\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_MS_DATA << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: MS_ERROR
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
    assertEvents_MS_ERROR_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_MS_ERROR)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event MS_ERROR\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_MS_ERROR << "\n";
  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void MotionTrackingGTestBase ::
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

  void MotionTrackingGTestBase ::
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

} // end namespace App
