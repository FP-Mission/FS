#include "Fw/Types/BasicTypes.hpp"
#include "App/SenseHat/Config/ICM20948Config.h"

namespace App {

  class Icm
    {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SenseHat
      //!
        Icm();

        void cycle();
         

      //! Destroy object SenseHat
      //!
      ~Icm(void);

      IMU_ST_ANGLES_DATA& getAngles();
      IMU_ST_SENSOR_DATA& getGyro();
      IMU_ST_SENSOR_DATA& getAccel();
      IMU_ST_SENSOR_DATA& getMagn();

      private:
        int fd;
        float Kp=4.50f;   // proportional gain governs rate of convergence to accelerometer/magnetometer
        float Ki=1.0f;    // integral gain governs rate of convergence of gyroscope biases

        float angles[3];
        float q0, q1, q2, q3; 

        IMU_ST_SENSOR_DATA gstGyroOffset ={0,0,0};  
        IMU_EN_SENSOR_TYPE enMotionSensorType;
        IMU_ST_ANGLES_DATA stAngles;
        IMU_ST_SENSOR_DATA stGyroRawData;
        IMU_ST_SENSOR_DATA stAccelRawData;
        IMU_ST_SENSOR_DATA stMagnRawData;


        void imuAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
        float invSqrt(float x);

        void icm20948init(void);
        bool icm20948Check(void);
        void icm20948GyroRead(short int* ps16X, short int* ps16Y, short int* ps16Z);
        void icm20948AccelRead(short int* ps16X, short int* ps16Y, short int* ps16Z);
        void icm20948MagRead(short int* ps16X, short int* ps16Y, short int* ps16Z);
        bool icm20948MagCheck(void);
        void icm20948CalAvgValue(unsigned char  *pIndex, short int *pAvgBuffer, short int InVal, int *pOutVal);
        void icm20948GyroOffset(void);
        void icm20948ReadSecondary(unsigned char  u8I2CAddr, unsigned char  u8RegAddr, unsigned char  u8Len, unsigned char  *pu8data);
        void icm20948WriteSecondary(unsigned char  u8I2CAddr, unsigned char  u8RegAddr, unsigned char  u8data);

        void imuInit(IMU_EN_SENSOR_TYPE *penMotionSensorType);
        void imuDataGet(IMU_ST_ANGLES_DATA *pstAngles, 
        IMU_ST_SENSOR_DATA *pstGyroRawData,
        IMU_ST_SENSOR_DATA *pstAccelRawData,
        IMU_ST_SENSOR_DATA *pstMagnRawData); 
        char readOneByte(char reg);
        void writeOneByte(char reg, char val);
    };

} // end namespace App

