// ======================================================================
// \title  SenseHat/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for SenseHat component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SenseHat_GTEST_BASE_HPP
#define SenseHat_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_SHTTemperature_SIZE(size) \
  this->assert_from_SHTTemperature_size(__FILE__, __LINE__, size)

#define ASSERT_from_SHTTemperature(index, _result) \
  { \
    ASSERT_GT(this->fromPortHistory_SHTTemperature->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_SHTTemperature\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_SHTTemperature->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_SHTTemperature& _e = \
      this->fromPortHistory_SHTTemperature->at(index); \
    ASSERT_EQ(_result, _e.result) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument result at index " \
    << index \
    << " in history of from_SHTTemperature\n" \
    << "  Expected: " << _result << "\n" \
    << "  Actual:   " << _e.result << "\n"; \
  }

#define ASSERT_from_SHTHumidity_SIZE(size) \
  this->assert_from_SHTHumidity_size(__FILE__, __LINE__, size)

#define ASSERT_from_SHTHumidity(index, _result) \
  { \
    ASSERT_GT(this->fromPortHistory_SHTHumidity->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_SHTHumidity\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_SHTHumidity->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_SHTHumidity& _e = \
      this->fromPortHistory_SHTHumidity->at(index); \
    ASSERT_EQ(_result, _e.result) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument result at index " \
    << index \
    << " in history of from_SHTHumidity\n" \
    << "  Expected: " << _result << "\n" \
    << "  Actual:   " << _e.result << "\n"; \
  }

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

namespace App {

  //! \class SenseHatGTestBase
  //! \brief Auto-generated base class for SenseHat component Google Test harness
  //!
  class SenseHatGTestBase :
    public SenseHatTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SenseHatGTestBase
      //!
      SenseHatGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SenseHatGTestBase
      //!
      virtual ~SenseHatGTestBase(void);

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
      // From port: SHTTemperature
      // ----------------------------------------------------------------------

      void assert_from_SHTTemperature_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: SHTHumidity
      // ----------------------------------------------------------------------

      void assert_from_SHTHumidity_size(
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

  };

} // end namespace App

#endif
