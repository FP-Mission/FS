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
// Macros for command history assertions
// ----------------------------------------------------------------------

#define ASSERT_CMD_RESPONSE_SIZE(size) \
  this->assertCmdResponse_size(__FILE__, __LINE__, size)

#define ASSERT_CMD_RESPONSE(index, opCode, cmdSeq, response) \
  this->assertCmdResponse(__FILE__, __LINE__, index, opCode, cmdSeq, response)

// ----------------------------------------------------------------------
// Macros for event history assertions
// ----------------------------------------------------------------------

#define ASSERT_EVENTS_SIZE(size) \
  this->assertEvents_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_MS_DATA_SIZE(size) \
  this->assertEvents_MS_DATA_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_MS_ERROR_SIZE(size) \
  this->assertEvents_MS_ERROR_size(__FILE__, __LINE__, size)

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_SHT_SIZE(size) \
  this->assert_from_SHT_size(__FILE__, __LINE__, size)

#define ASSERT_from_SHT(index, _temperature, _humidity) \
  { \
    ASSERT_GT(this->fromPortHistory_SHT->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_SHT\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_SHT->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_SHT& _e = \
      this->fromPortHistory_SHT->at(index); \
    ASSERT_EQ(_temperature, _e.temperature) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument temperature at index " \
    << index \
    << " in history of from_SHT\n" \
    << "  Expected: " << _temperature << "\n" \
    << "  Actual:   " << _e.temperature << "\n"; \
    ASSERT_EQ(_humidity, _e.humidity) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument humidity at index " \
    << index \
    << " in history of from_SHT\n" \
    << "  Expected: " << _humidity << "\n" \
    << "  Actual:   " << _e.humidity << "\n"; \
  }

#define ASSERT_from_LPS_SIZE(size) \
  this->assert_from_LPS_size(__FILE__, __LINE__, size)

#define ASSERT_from_LPS(index, _temperature, _pressure) \
  { \
    ASSERT_GT(this->fromPortHistory_LPS->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_LPS\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_LPS->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_LPS& _e = \
      this->fromPortHistory_LPS->at(index); \
    ASSERT_EQ(_temperature, _e.temperature) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument temperature at index " \
    << index \
    << " in history of from_LPS\n" \
    << "  Expected: " << _temperature << "\n" \
    << "  Actual:   " << _e.temperature << "\n"; \
    ASSERT_EQ(_pressure, _e.pressure) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument pressure at index " \
    << index \
    << " in history of from_LPS\n" \
    << "  Expected: " << _pressure << "\n" \
    << "  Actual:   " << _e.pressure << "\n"; \
  }

#define ASSERT_from_ICM_SIZE(size) \
  this->assert_from_ICM_size(__FILE__, __LINE__, size)

#define ASSERT_from_ICM(index, _angles, _gyro, _accel, _magn) \
  { \
    ASSERT_GT(this->fromPortHistory_ICM->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_ICM\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_ICM->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_ICM& _e = \
      this->fromPortHistory_ICM->at(index); \
    ASSERT_EQ(_angles, _e.angles) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument angles at index " \
    << index \
    << " in history of from_ICM\n" \
    << "  Expected: " << _angles << "\n" \
    << "  Actual:   " << _e.angles << "\n"; \
    ASSERT_EQ(_gyro, _e.gyro) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument gyro at index " \
    << index \
    << " in history of from_ICM\n" \
    << "  Expected: " << _gyro << "\n" \
    << "  Actual:   " << _e.gyro << "\n"; \
    ASSERT_EQ(_accel, _e.accel) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument accel at index " \
    << index \
    << " in history of from_ICM\n" \
    << "  Expected: " << _accel << "\n" \
    << "  Actual:   " << _e.accel << "\n"; \
    ASSERT_EQ(_magn, _e.magn) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument magn at index " \
    << index \
    << " in history of from_ICM\n" \
    << "  Expected: " << _magn << "\n" \
    << "  Actual:   " << _e.magn << "\n"; \
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
      // Commands
      // ----------------------------------------------------------------------

      //! Assert size of command response history
      //!
      void assertCmdResponse_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      //! Assert command response in history at index
      //!
      void assertCmdResponse(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
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
      // From port: SHT
      // ----------------------------------------------------------------------

      void assert_from_SHT_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: LPS
      // ----------------------------------------------------------------------

      void assert_from_LPS_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: ICM
      // ----------------------------------------------------------------------

      void assert_from_ICM_size(
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
