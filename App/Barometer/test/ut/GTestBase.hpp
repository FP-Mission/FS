// ======================================================================
// \title  Barometer/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for Barometer component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Barometer_GTEST_BASE_HPP
#define Barometer_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for telemetry history assertions
// ----------------------------------------------------------------------

#define ASSERT_TLM_SIZE(size) \
  this->assertTlm_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_BAROMETER_TEMP_SIZE(size) \
  this->assertTlm_BAROMETER_TEMP_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_BAROMETER_TEMP(index, value) \
  this->assertTlm_BAROMETER_TEMP(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_BAROMETER_PRESS_SIZE(size) \
  this->assertTlm_BAROMETER_PRESS_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_BAROMETER_PRESS(index, value) \
  this->assertTlm_BAROMETER_PRESS(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_BAROMETER_ALT_SIZE(size) \
  this->assertTlm_BAROMETER_ALT_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_BAROMETER_ALT(index, value) \
  this->assertTlm_BAROMETER_ALT(__FILE__, __LINE__, index, value)

// ----------------------------------------------------------------------
// Macros for event history assertions
// ----------------------------------------------------------------------

#define ASSERT_EVENTS_SIZE(size) \
  this->assertEvents_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_MS_DATA_SIZE(size) \
  this->assertEvents_MS_DATA_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_MS_DATA(index, _temp, _pres, _alt) \
  this->assertEvents_MS_DATA(__FILE__, __LINE__, index, _temp, _pres, _alt)

#define ASSERT_EVENTS_MS_ERROR_SIZE(size) \
  this->assertEvents_MS_ERROR_size(__FILE__, __LINE__, size)

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_PingOut_SIZE(size) \
  this->assert_from_PingOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_PingOut(index, _key) \
  { \
    ASSERT_GT(this->fromPortHistory_PingOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_PingOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_PingOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_PingOut& _e = \
      this->fromPortHistory_PingOut->at(index); \
    ASSERT_EQ(_key, _e.key) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument key at index " \
    << index \
    << " in history of from_PingOut\n" \
    << "  Expected: " << _key << "\n" \
    << "  Actual:   " << _e.key << "\n"; \
  }

#define ASSERT_from_DataOut_SIZE(size) \
  this->assert_from_DataOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_DataOut(index, _altitude, _pressure, _temperature) \
  { \
    ASSERT_GT(this->fromPortHistory_DataOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_DataOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_DataOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_DataOut& _e = \
      this->fromPortHistory_DataOut->at(index); \
    ASSERT_EQ(_altitude, _e.altitude) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument altitude at index " \
    << index \
    << " in history of from_DataOut\n" \
    << "  Expected: " << _altitude << "\n" \
    << "  Actual:   " << _e.altitude << "\n"; \
    ASSERT_EQ(_pressure, _e.pressure) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument pressure at index " \
    << index \
    << " in history of from_DataOut\n" \
    << "  Expected: " << _pressure << "\n" \
    << "  Actual:   " << _e.pressure << "\n"; \
    ASSERT_EQ(_temperature, _e.temperature) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument temperature at index " \
    << index \
    << " in history of from_DataOut\n" \
    << "  Expected: " << _temperature << "\n" \
    << "  Actual:   " << _e.temperature << "\n"; \
  }

namespace App {

  //! \class BarometerGTestBase
  //! \brief Auto-generated base class for Barometer component Google Test harness
  //!
  class BarometerGTestBase :
    public BarometerTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object BarometerGTestBase
      //!
      BarometerGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object BarometerGTestBase
      //!
      virtual ~BarometerGTestBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Telemetry
      // ----------------------------------------------------------------------

      //! Assert size of telemetry history
      //!
      void assertTlm_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: BAROMETER_TEMP
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_BAROMETER_TEMP_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_BAROMETER_TEMP(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const F32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: BAROMETER_PRESS
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_BAROMETER_PRESS_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_BAROMETER_PRESS(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const F32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: BAROMETER_ALT
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_BAROMETER_ALT_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_BAROMETER_ALT(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U16& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Events
      // ----------------------------------------------------------------------

      void assertEvents_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: MS_DATA
      // ----------------------------------------------------------------------

      void assertEvents_MS_DATA_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_MS_DATA(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const F32 temp, /*!< LPS temp*/
          const F32 pres, /*!< LPS pres*/
          const U16 alt /*!< alt calc*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: MS_ERROR
      // ----------------------------------------------------------------------

      void assertEvents_MS_ERROR_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      void assertFromPortHistory_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: PingOut
      // ----------------------------------------------------------------------

      void assert_from_PingOut_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: DataOut
      // ----------------------------------------------------------------------

      void assert_from_DataOut_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace App

#endif
