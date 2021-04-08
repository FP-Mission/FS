#include "Vector.hpp"

namespace App{
    Vector::Vector() : Serializable(){

    }

    Vector::Vector(I16 x, I16 y, I16 z) : Serializable() {
        this->x = x;
        this->y = y;
        this->z = z;
    }


    Vector::~Vector(){

    }

    I16 Vector::getX(){
        return x;
    }
    I16 Vector::getY(){
        return y;
    }
    I16 Vector::getZ(){
        return z;
    }

    void Vector::setX(I16 x){
        this->x = x;
    }
    void Vector::setY(I16 y){
        this->y = y;
    }
    void Vector::setZ(I16 z){
        this->z = z;
    }

    void Vector::setXyz(I16 x, I16 y, I16 z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Fw::SerializeStatus Vector::serialize(Fw::SerializeBufferBase& buffer) const{ // !< Serialize method

        Fw::SerializeStatus stat = Fw::FW_SERIALIZE_OK;
        stat = buffer.serialize(this->x);
        
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        stat = buffer.serialize(this->y);
        
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        return stat = buffer.serialize(this->z);
    }

    Fw::SerializeStatus Vector::deserialize(Fw::SerializeBufferBase& buffer){ // !< Deserialize method
        Fw::SerializeStatus stat = Fw::FW_SERIALIZE_OK;

        stat = buffer.deserialize(this->x);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        stat = buffer.deserialize(this->y);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

       return buffer.deserialize(this->z);

    }
}
