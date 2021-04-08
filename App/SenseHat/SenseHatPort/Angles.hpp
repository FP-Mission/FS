#ifndef ANGLES_HPP_
#define ANGLES_HPP_

#include <Fw/Types/Serializable.hpp>
#include <Fw/Types/BasicTypes.hpp>

namespace App {


class Angles : public Fw::Serializable {

    public:

        enum {
        SERIALIZED_SIZE = 3*sizeof(F32)
        };

        Angles();

        Angles(F32 roll, F32 pitch, F32 yaw);


        ~Angles();

        F32 getRoll();
        F32 getPitch();
        F32 getYaw();

        void setRoll(F32 roll);
        void setPitch(F32 pitch);
        void setYaw(F32 yaw);

        void setRollPitchYaw(F32 roll, F32 pitch, F32 yaw);
        
        Fw::SerializeStatus serialize(Fw::SerializeBufferBase& buffer) const; // !< Serialize method
        Fw::SerializeStatus deserialize(Fw::SerializeBufferBase& buffer); // !< Deserialize method


    PRIVATE:
        F32 roll;
        F32 pitch;
        F32 yaw;

    };
} // end namespace App
#endif 

