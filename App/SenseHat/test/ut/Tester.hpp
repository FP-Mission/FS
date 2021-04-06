// ======================================================================
// \title  SenseHat/test/ut/Tester.hpp
// \author root
// \brief  hpp file for SenseHat test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "App/SenseHat/SenseHatComponentImpl.hpp"

namespace App {

  class Tester :
    public SenseHatGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object Tester
      //!
      Tester(void);

      //! Destroy object Tester
      //!
      ~Tester(void);

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! To do
      //!
      void toDo(void);

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_SHTTemperature
      //!
      void from_SHTTemperature_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< sense hat data*/
      );

      //! Handler for from_SHTHumidity
      //!
      void from_SHTHumidity_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< sense hat data*/
      );

      //! Handler for from_PingOut
      //!
      void from_PingOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts(void);

      //! Initialize components
      //!
      void initComponents(void);

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      SenseHatComponentImpl component;

  };

} // end namespace App

#endif
