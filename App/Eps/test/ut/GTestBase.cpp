// ======================================================================
// \title  Eps/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for Eps component Google Test harness base class
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

  EpsGTestBase ::
    EpsGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
        EpsTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  EpsGTestBase ::
    ~EpsGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Commands
  // ----------------------------------------------------------------------

  void EpsGTestBase ::
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

  void EpsGTestBase ::
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

  void EpsGTestBase ::
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
  // Channel: Eps_BatteryVoltage
  // ----------------------------------------------------------------------

  void EpsGTestBase ::
    assertTlm_Eps_BatteryVoltage_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_Eps_BatteryVoltage->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel Eps_BatteryVoltage\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_Eps_BatteryVoltage->size() << "\n";
  }

  void EpsGTestBase ::
    assertTlm_Eps_BatteryVoltage(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U16& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_Eps_BatteryVoltage->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel Eps_BatteryVoltage\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_Eps_BatteryVoltage->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_Eps_BatteryVoltage& e =
      this->tlmHistory_Eps_BatteryVoltage->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telemetry channel Eps_BatteryVoltage\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void EpsGTestBase ::
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
  // Event: Eps_LowBattery
  // ----------------------------------------------------------------------

  void EpsGTestBase ::
    assertEvents_Eps_LowBattery_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_Eps_LowBattery->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event Eps_LowBattery\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_Eps_LowBattery->size() << "\n";
  }

  void EpsGTestBase ::
    assertEvents_Eps_LowBattery(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U16 voltage
    ) const
  {
    ASSERT_GT(this->eventHistory_Eps_LowBattery->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event Eps_LowBattery\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_Eps_LowBattery->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_Eps_LowBattery& e =
      this->eventHistory_Eps_LowBattery->at(__index);
    ASSERT_EQ(voltage, e.voltage)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument voltage at index "
      << __index
      << " in history of event Eps_LowBattery\n"
      << "  Expected: " << voltage << "\n"
      << "  Actual:   " << e.voltage << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: Eps_CriticallyLowBattery
  // ----------------------------------------------------------------------

  void EpsGTestBase ::
    assertEvents_Eps_CriticallyLowBattery_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_Eps_CriticallyLowBattery->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event Eps_CriticallyLowBattery\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_Eps_CriticallyLowBattery->size() << "\n";
  }

  void EpsGTestBase ::
    assertEvents_Eps_CriticallyLowBattery(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U16 voltage
    ) const
  {
    ASSERT_GT(this->eventHistory_Eps_CriticallyLowBattery->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event Eps_CriticallyLowBattery\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_Eps_CriticallyLowBattery->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_Eps_CriticallyLowBattery& e =
      this->eventHistory_Eps_CriticallyLowBattery->at(__index);
    ASSERT_EQ(voltage, e.voltage)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument voltage at index "
      << __index
      << " in history of event Eps_CriticallyLowBattery\n"
      << "  Expected: " << voltage << "\n"
      << "  Actual:   " << e.voltage << "\n";
  }

} // end namespace App
