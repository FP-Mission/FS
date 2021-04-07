#include "Fw/Types/BasicTypes.hpp"

namespace App {

  class Shtc3
    {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SenseHat
      //!
        Shtc3();

        void cycle();

        void writeCommand(U16 cmd);
        void wakeUp();

        void sleep();

        void softReset();

        void readData();

        F32 getTemperatureValue();

        F32 getHumidityValue();
         

      //! Destroy object SenseHat
      //!
      ~Shtc3(void);

      private:
        int fd;
        F32 temperatureValue,humidityValue;

        I8 checkCrc(I8 data[],U8 len,U8 checksum);

    };

} // end namespace App

