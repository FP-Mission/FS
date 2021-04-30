// ======================================================================
// \title  Thermometer/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for Thermometer component Google Test harness base class
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

  ThermometerGTestBase ::
    ThermometerGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
        ThermometerTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  ThermometerGTestBase ::
    ~ThermometerGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Telemetry
  // ----------------------------------------------------------------------

  void ThermometerGTestBase ::
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
  // Channel: THERMOMETER_TEMP
  // ----------------------------------------------------------------------

  void ThermometerGTestBase ::
    assertTlm_THERMOMETER_TEMP_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_THERMOMETER_TEMP->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel THERMOMETER_TEMP\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_THERMOMETER_TEMP->size() << "\n";
  }

  void ThermometerGTestBase ::
    assertTlm_THERMOMETER_TEMP(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const F32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_THERMOMETER_TEMP->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel THERMOMETER_TEMP\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_THERMOMETER_TEMP->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_THERMOMETER_TEMP& e =
      this->tlmHistory_THERMOMETER_TEMP->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel THERMOMETER_TEMP\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: THERMOMETER_HUMI
  // ----------------------------------------------------------------------

  void ThermometerGTestBase ::
    assertTlm_THERMOMETER_HUMI_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_THERMOMETER_HUMI->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel THERMOMETER_HUMI\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_THERMOMETER_HUMI->size() << "\n";
  }

  void ThermometerGTestBase ::
    assertTlm_THERMOMETER_HUMI(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const F32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_THERMOMETER_HUMI->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel THERMOMETER_HUMI\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_THERMOMETER_HUMI->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_THERMOMETER_HUMI& e =
      this->tlmHistory_THERMOMETER_HUMI->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel THERMOMETER_HUMI\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void ThermometerGTestBase ::
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

  void ThermometerGTestBase ::
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

  void ThermometerGTestBase ::
    assertEvents_MS_DATA(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const F32 temp,
        const F32 humi
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
    ASSERT_EQ(humi, e.humi)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument humi at index "
      << __index
      << " in history of event MS_DATA\n"
      << "  Expected: " << humi << "\n"
      << "  Actual:   " << e.humi << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: MS_ERROR
  // ----------------------------------------------------------------------

  void ThermometerGTestBase ::
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

  void ThermometerGTestBase ::
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

  void ThermometerGTestBase ::
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
