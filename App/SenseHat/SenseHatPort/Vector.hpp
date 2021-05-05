#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <Fw/Types/Serializable.hpp>
#include <Fw/Types/BasicTypes.hpp>

namespace App {


class Vector : public Fw::Serializable {

    public:

        enum {
        SERIALIZED_SIZE = 3*sizeof(I16)
        };

        Vector();

        Vector(I16 x, I16 y, I16 z);


        ~Vector();

        I16 getX();
        I16 getY();
        I16 getZ();

        void setX(I16 x);
        void setY(I16 y);
        void setZ(I16 z);

        void setXyz(I16 x, I16 y, I16 z);
        
        Fw::SerializeStatus serialize(Fw::SerializeBufferBase& buffer) const; // !< Serialize method
        Fw::SerializeStatus deserialize(Fw::SerializeBufferBase& buffer); // !< Deserialize method


    PRIVATE:
        I16 x;
        I16 y;
        I16 z;

    };
} // end namespace App
#endif 

