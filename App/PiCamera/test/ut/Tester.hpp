// ======================================================================
// \title  PiCamera/test/ut/Tester.hpp
// \author root
// \brief  hpp file for PiCamera test harness implementation class
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
#include "App/PiCamera/PiCameraComponentImpl.hpp"

namespace App {

  class Tester :
    public PiCameraGTestBase
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
      void testCreatedDirectories(void);
      void testFile(void);
      void testBarometerPort(void);
      void testPositionPort(void);

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_PingOut
      //!
      void from_PingOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Handler for from_PictureOut
      //!
      void from_PictureOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::ComBuffer &data, /*!< Buffer containing packet data*/
          U32 context /*!< Call context value; meaning chosen by user*/
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
      PiCameraComponentImpl component;

  };

} // end namespace App

#endif