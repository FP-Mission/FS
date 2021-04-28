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

      //! Handler for from_SHT
      //!
      void from_SHT_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< sht temperature*/
          F32 humidity /*!< sht humidity*/
      );

      //! Handler for from_LPS
      //!
      void from_LPS_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 temperature, /*!< lps temperature*/
          F32 pressure /*!< lps humidity*/
      );

      //! Handler for from_ICM
      //!
      void from_ICM_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          App::Angles &angles, 
          App::Vector &gyro, 
          App::Vector &accel, 
          App::Vector &magn 
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
