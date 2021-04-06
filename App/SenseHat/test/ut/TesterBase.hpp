// ======================================================================
// \title  SenseHat/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for SenseHat component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SenseHat_TESTER_BASE_HPP
#define SenseHat_TESTER_BASE_HPP

#include <App/SenseHat/SenseHatComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace App {

  //! \class SenseHatTesterBase
  //! \brief Auto-generated base class for SenseHat component test harness
  //!
  class SenseHatTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object SenseHatTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect Schedin to to_Schedin[portNum]
      //!
      void connect_to_Schedin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputSchedPort *const Schedin /*!< The port*/
      );

      //! Connect PingIn to to_PingIn[portNum]
      //!
      void connect_to_PingIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputPingPort *const PingIn /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from SHTTemperature
      //!
      //! \return from_SHTTemperature[portNum]
      //!
      App::InputSenseHatFloatDataPort* get_from_SHTTemperature(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from SHTHumidity
      //!
      //! \return from_SHTHumidity[portNum]
      //!
      App::InputSenseHatFloatDataPort* get_from_SHTHumidity(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from PingOut
      //!
      //! \return from_PingOut[portNum]
      //!
      Svc::InputPingPort* get_from_PingOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SenseHatTesterBase
      //!
      SenseHatTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SenseHatTesterBase
      //!
      virtual ~SenseHatTesterBase(void);

      // ----------------------------------------------------------------------
      // Test history
      // ----------------------------------------------------------------------

    protected:

      //! \class History
      //! \brief A history of port inputs
      //!
      template <typename T> class History {

        public:

          //! Create a History
          //!
          History(
              const U32 maxSize /*!< The maximum history size*/
          ) :
              numEntries(0),
              maxSize(maxSize)
          {
            this->entries = new T[maxSize];
          }

          //! Destroy a History
          //!
          ~History() {
            delete[] this->entries;
          }

          //! Clear the history
          //!
          void clear() { this->numEntries = 0; }

          //! Push an item onto the history
          //!
          void push_back(
              T entry /*!< The item*/
          ) {
            FW_ASSERT(this->numEntries < this->maxSize);
            entries[this->numEntries++] = entry;
          }

          //! Get an item at an index
          //!
          //! \return The item at index i
          //!
          T at(
              const U32 i /*!< The index*/
          ) const {
            FW_ASSERT(i < this->numEntries);
            return entries[i];
          }

          //! Get the number of entries in the history
          //!
          //! \return The number of entries in the history
          //!
          U32 size(void) const { return this->numEntries; }

        private:

          //! The number of entries in the history
          //!
          U32 numEntries;

          //! The maximum history size
          //!
          const U32 maxSize;

          //! The entries
          //!
          T *entries;

      };

      //! Clear all history
      //!
      void clearHistory(void);

    protected:

      // ----------------------------------------------------------------------
      // Handler prototypes for typed from ports
      // ----------------------------------------------------------------------

      //! Handler prototype for from_SHTTemperature
      //!
      virtual void from_SHTTemperature_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< sense hat data*/
      ) = 0;

      //! Handler base function for from_SHTTemperature
      //!
      void from_SHTTemperature_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< sense hat data*/
      );

      //! Handler prototype for from_SHTHumidity
      //!
      virtual void from_SHTHumidity_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< sense hat data*/
      ) = 0;

      //! Handler base function for from_SHTHumidity
      //!
      void from_SHTHumidity_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< sense hat data*/
      );

      //! Handler prototype for from_PingOut
      //!
      virtual void from_PingOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      ) = 0;

      //! Handler base function for from_PingOut
      //!
      void from_PingOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Histories for typed from ports
      // ----------------------------------------------------------------------

      //! Clear from port history
      //!
      void clearFromPortHistory(void);

      //! The total number of from port entries
      //!
      U32 fromPortHistorySize;

      //! Push an entry on the history for from_SHTTemperature
      void pushFromPortEntry_SHTTemperature(
          F32 result /*!< sense hat data*/
      );

      //! A history entry for from_SHTTemperature
      //!
      typedef struct {
          F32 result;
      } FromPortEntry_SHTTemperature;

      //! The history for from_SHTTemperature
      //!
      History<FromPortEntry_SHTTemperature>
        *fromPortHistory_SHTTemperature;

      //! Push an entry on the history for from_SHTHumidity
      void pushFromPortEntry_SHTHumidity(
          F32 result /*!< sense hat data*/
      );

      //! A history entry for from_SHTHumidity
      //!
      typedef struct {
          F32 result;
      } FromPortEntry_SHTHumidity;

      //! The history for from_SHTHumidity
      //!
      History<FromPortEntry_SHTHumidity>
        *fromPortHistory_SHTHumidity;

      //! Push an entry on the history for from_PingOut
      void pushFromPortEntry_PingOut(
          U32 key /*!< Value to return to pinger*/
      );

      //! A history entry for from_PingOut
      //!
      typedef struct {
          U32 key;
      } FromPortEntry_PingOut;

      //! The history for from_PingOut
      //!
      History<FromPortEntry_PingOut>
        *fromPortHistory_PingOut;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to Schedin
      //!
      void invoke_to_Schedin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Invoke the to port connected to PingIn
      //!
      void invoke_to_PingIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of from_SHTTemperature ports
      //!
      //! \return The number of from_SHTTemperature ports
      //!
      NATIVE_INT_TYPE getNum_from_SHTTemperature(void) const;

      //! Get the number of from_SHTHumidity ports
      //!
      //! \return The number of from_SHTHumidity ports
      //!
      NATIVE_INT_TYPE getNum_from_SHTHumidity(void) const;

      //! Get the number of to_Schedin ports
      //!
      //! \return The number of to_Schedin ports
      //!
      NATIVE_INT_TYPE getNum_to_Schedin(void) const;

      //! Get the number of to_PingIn ports
      //!
      //! \return The number of to_PingIn ports
      //!
      NATIVE_INT_TYPE getNum_to_PingIn(void) const;

      //! Get the number of from_PingOut ports
      //!
      //! \return The number of from_PingOut ports
      //!
      NATIVE_INT_TYPE getNum_from_PingOut(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_Schedin[portNum] is connected
      //!
      bool isConnected_to_Schedin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_PingIn[portNum] is connected
      //!
      bool isConnected_to_PingIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to Schedin
      //!
      Svc::OutputSchedPort m_to_Schedin[1];

      //! To port connected to PingIn
      //!
      Svc::OutputPingPort m_to_PingIn[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to SHTTemperature
      //!
      App::InputSenseHatFloatDataPort m_from_SHTTemperature[1];

      //! From port connected to SHTHumidity
      //!
      App::InputSenseHatFloatDataPort m_from_SHTHumidity[1];

      //! From port connected to PingOut
      //!
      Svc::InputPingPort m_from_PingOut[1];

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_SHTTemperature
      //!
      static void from_SHTTemperature_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< sense hat data*/
      );

      //! Static function for port from_SHTHumidity
      //!
      static void from_SHTHumidity_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< sense hat data*/
      );

      //! Static function for port from_PingOut
      //!
      static void from_PingOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

  };

} // end namespace App

#endif
