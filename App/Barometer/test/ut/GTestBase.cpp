// ======================================================================
// \title  Barometer/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for Barometer component Google Test harness base class
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

  BarometerGTestBase ::
    BarometerGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
        BarometerTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  BarometerGTestBase ::
    ~BarometerGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Telemetry
  // ----------------------------------------------------------------------

  void BarometerGTestBase ::
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
  // Channel: BAROMETER_TEMP
  // ----------------------------------------------------------------------

  void BarometerGTestBase ::
    assertTlm_BAROMETER_TEMP_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_BAROMETER_TEMP->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel BAROMETER_TEMP\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_BAROMETER_TEMP->size() << "\n";
  }

  void BarometerGTestBase ::
    assertTlm_BAROMETER_TEMP(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const F32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_BAROMETER_TEMP->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel BAROMETER_TEMP\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_BAROMETER_TEMP->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_BAROMETER_TEMP& e =
      this->tlmHistory_BAROMETER_TEMP->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel BAROMETER_TEMP\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: BAROMETER_PRESS
  // ----------------------------------------------------------------------

  void BarometerGTestBase ::
    assertTlm_BAROMETER_PRESS_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_BAROMETER_PRESS->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel BAROMETER_PRESS\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_BAROMETER_PRESS->size() << "\n";
  }

  void BarometerGTestBase ::
    assertTlm_BAROMETER_PRESS(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const F32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_BAROMETER_PRESS->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel BAROMETER_PRESS\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_BAROMETER_PRESS->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_BAROMETER_PRESS& e =
      this->tlmHistory_BAROMETER_PRESS->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel BAROMETER_PRESS\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: BAROMETER_ALT
  // ----------------------------------------------------------------------

  void BarometerGTestBase ::
    assertTlm_BAROMETER_ALT_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_BAROMETER_ALT->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel BAROMETER_ALT\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_BAROMETER_ALT->size() << "\n";
  }

  void BarometerGTestBase ::
    assertTlm_BAROMETER_ALT(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U16& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_BAROMETER_ALT->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel BAROMETER_ALT\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_BAROMETER_ALT->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_BAROMETER_ALT& e =
      this->tlmHistory_BAROMETER_ALT->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel BAROMETER_ALT\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void BarometerGTestBase ::
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

  void BarometerGTestBase ::
    assertEvents_MS_DATA_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_MS_DATA->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event MS_DATA\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_MS_DATA->size() << "\n";
  }

  void BarometerGTestBase ::
    assertEvents_MS_DATA(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const F32 temp,
        const F32 pres,
        const U16 alt
    ) const
  {
    ASSERT_GT(this->eventHistory_MS_DATA->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event MS_DATA\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_MS_DATA->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_MS_DATA& e =
      this->eventHistory_MS_DATA->at(__index);
    ASSERT_EQ(temp, e.temp)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument temp at index "
      << __index
      << " in history of event MS_DATA\n"
      << "  Expected: " << temp << "\n"
      << "  Actual:   " << e.temp << "\n";
    ASSERT_EQ(pres, e.pres)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument pres at index "
      << __index
      << " in history of event MS_DATA\n"
      << "  Expected: " << pres << "\n"
      << "  Actual:   " << e.pres << "\n";
    ASSERT_EQ(alt, e.alt)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument alt at index "
      << __index
      << " in history of event MS_DATA\n"
      << "  Expected: " << alt << "\n"
      << "  Actual:   " << e.alt << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: MS_ERROR
  // ----------------------------------------------------------------------

  void BarometerGTestBase ::
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

  void BarometerGTestBase ::
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

  void BarometerGTestBase ::
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
