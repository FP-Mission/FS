// ======================================================================
// \title  PiCamera/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for PiCamera component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef PiCamera_GTEST_BASE_HPP
#define PiCamera_GTEST_BASE_HPP

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
// Macros for telemetry history assertions
// ----------------------------------------------------------------------

#define ASSERT_TLM_SIZE(size) \
  this->assertTlm_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_PiCam_PictureCnt_SIZE(size) \
  this->assertTlm_PiCam_PictureCnt_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_PiCam_PictureCnt(index, value) \
  this->assertTlm_PiCam_PictureCnt(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_PiCam_PictureSize_SIZE(size) \
  this->assertTlm_PiCam_PictureSize_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_PiCam_PictureSize(index, value) \
  this->assertTlm_PiCam_PictureSize(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_PiCam_Timeinterval_SIZE(size) \
  this->assertTlm_PiCam_Timeinterval_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_PiCam_Timeinterval(index, value) \
  this->assertTlm_PiCam_Timeinterval(__FILE__, __LINE__, index, value)

// ----------------------------------------------------------------------
// Macros for event history assertions
// ----------------------------------------------------------------------

#define ASSERT_EVENTS_SIZE(size) \
  this->assertEvents_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_PiCam_PictureTaken_SIZE(size) \
  this->assertEvents_PiCam_PictureTaken_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_PiCam_PositionUpdate_SIZE(size) \
  this->assertEvents_PiCam_PositionUpdate_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_PiCam_BarometerDataUpdate_SIZE(size) \
  this->assertEvents_PiCam_BarometerDataUpdate_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_PiCam_BarometerDataUpdate(index, _temp, _pressure, _altitude) \
  this->assertEvents_PiCam_BarometerDataUpdate(__FILE__, __LINE__, index, _temp, _pressure, _altitude)

#define ASSERT_EVENTS_PiCam_PictureError_SIZE(size) \
  this->assertEvents_PiCam_PictureError_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_PiCam_PictureError(index, _code) \
  this->assertEvents_PiCam_PictureError(__FILE__, __LINE__, index, _code)

#define ASSERT_EVENTS_PiCam_SetTimeInterval_SIZE(size) \
  this->assertEvents_PiCam_SetTimeInterval_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_PiCam_SetTimeInterval(index, _timeInterval) \
  this->assertEvents_PiCam_SetTimeInterval(__FILE__, __LINE__, index, _timeInterval)

#define ASSERT_EVENTS_PiCam_SetPictureSize_SIZE(size) \
  this->assertEvents_PiCam_SetPictureSize_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_PiCam_SetPictureSize(index, _width, _height) \
  this->assertEvents_PiCam_SetPictureSize(__FILE__, __LINE__, index, _width, _height)

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

#define ASSERT_from_PictureOut_SIZE(size) \
  this->assert_from_PictureOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_PictureOut(index, _data, _context) \
  { \
    ASSERT_GT(this->fromPortHistory_PictureOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_PictureOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_PictureOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_PictureOut& _e = \
      this->fromPortHistory_PictureOut->at(index); \
    ASSERT_EQ(_data, _e.data) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument data at index " \
    << index \
    << " in history of from_PictureOut\n" \
    << "  Expected: " << _data << "\n" \
    << "  Actual:   " << _e.data << "\n"; \
    ASSERT_EQ(_context, _e.context) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context at index " \
    << index \
    << " in history of from_PictureOut\n" \
    << "  Expected: " << _context << "\n" \
    << "  Actual:   " << _e.context << "\n"; \
  }

namespace App {

  //! \class PiCameraGTestBase
  //! \brief Auto-generated base class for PiCamera component Google Test harness
  //!
  class PiCameraGTestBase :
    public PiCameraTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object PiCameraGTestBase
      //!
      PiCameraGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object PiCameraGTestBase
      //!
      virtual ~PiCameraGTestBase(void);

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
      // Channel: PiCam_PictureCnt
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_PiCam_PictureCnt_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_PiCam_PictureCnt(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U8& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: PiCam_PictureSize
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_PiCam_PictureSize_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_PiCam_PictureSize(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const App::PictureSize& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: PiCam_Timeinterval
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_PiCam_Timeinterval_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_PiCam_Timeinterval(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U8& val /*!< The channel value*/
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
      // Event: PiCam_PictureTaken
      // ----------------------------------------------------------------------

      void assertEvents_PiCam_PictureTaken_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: PiCam_PositionUpdate
      // ----------------------------------------------------------------------

      void assertEvents_PiCam_PositionUpdate_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: PiCam_BarometerDataUpdate
      // ----------------------------------------------------------------------

      void assertEvents_PiCam_BarometerDataUpdate_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_PiCam_BarometerDataUpdate(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const F32 temp, /*!< temp*/
          const F32 pressure, /*!< temp*/
          const U16 altitude /*!< temp*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: PiCam_PictureError
      // ----------------------------------------------------------------------

      void assertEvents_PiCam_PictureError_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_PiCam_PictureError(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32 code /*!< Error code*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: PiCam_SetTimeInterval
      // ----------------------------------------------------------------------

      void assertEvents_PiCam_SetTimeInterval_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_PiCam_SetTimeInterval(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U8 timeInterval /*!< time interval*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: PiCam_SetPictureSize
      // ----------------------------------------------------------------------

      void assertEvents_PiCam_SetPictureSize_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_PiCam_SetPictureSize(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32 width, /*!< Picture width*/
          const U32 height /*!< Picture height*/
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
      // From port: PictureOut
      // ----------------------------------------------------------------------

      void assert_from_PictureOut_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace App

#endif
