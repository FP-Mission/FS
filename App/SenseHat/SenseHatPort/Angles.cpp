#include "Angles.hpp"

namespace App{
    Angles::Angles() : Serializable(){

    }

    Angles::Angles(F32 roll, F32 pitch, F32 yaw) : Serializable() {
        this->roll = roll;
        this->pitch = pitch;
        this->yaw = yaw;
    }


    Angles::~Angles(){

    }

    F32 Angles::getRoll(){
        return roll;
    }
    F32 Angles::getPitch(){
        return pitch;
    }
    F32 Angles::getYaw(){
        return yaw;
    }

    void Angles::setRoll(F32 roll){
        this->roll = roll;
    }
    void Angles::setPitch(F32 pitch){
        this->pitch = pitch;
    }
    void Angles::setYaw(F32 yaw){
        this->yaw = yaw;
    }

    void Angles::setRollPitchYaw(F32 roll, F32 pitch, F32 yaw){
        this->roll = roll;
        this->pitch = pitch;
        this->yaw = yaw;
    }

    Fw::SerializeStatus Angles::serialize(Fw::SerializeBufferBase& buffer) const{ // !< Serialiyawe method

        Fw::SerializeStatus stat = Fw::FW_SERIALIZE_OK;
        stat = buffer.serialize(static_cast<FwTimeBaseStoreType>(this->roll));
        
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        stat = buffer.serialize(static_cast<FwTimeBaseStoreType>(this->pitch));
        
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        return stat = buffer.serialize(static_cast<FwTimeBaseStoreType>(this->yaw));
    }

    Fw::SerializeStatus Angles::deserialize(Fw::SerializeBufferBase& buffer){ // !< Deserialiyawe method
        Fw::SerializeStatus stat = Fw::FW_SERIALIZE_OK;

        stat = buffer.deserialize(this->roll);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        stat = buffer.deserialize(this->pitch);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

       return buffer.deserialize(this->yaw);

    }
}
