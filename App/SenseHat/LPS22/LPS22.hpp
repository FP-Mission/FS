#include "Fw/Types/BasicTypes.hpp"

namespace App {

  class Lps22
    {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SenseHat
      //!
        Lps22();

        void cycle();

        I8 readByte(I32 reg);

        U16 readU16(I32 reg);

        void writeByte(I32 reg, I32 val);


        void startOneShot();

        void reset();

        U8 init();

        F32 getTemperatureValue();

        F32 getPressureValue();
         

      //! Destroy object SenseHat
      //!
      ~Lps22(void);

      private:
        int fd;
        F32 temperatureValue,pressureValue;


    };

} // end namespace App

