#include <phys2d/Body.h>

namespace phys2d{
    BodyData::BodyData(float mass_, float restitution_) : 
        restitution(restitution_) {
        setMass(mass_);
    }

    void BodyData::setMass(float mass_){
        mass = mass_;
        massinv = 1/mass_;
    }

    float BodyData::getMass(){
        return mass;
    }

    float BodyData::getMassInv(){
        return massinv;
    }

    Body::Body(std::unique_ptr<Shape> shape_, BodyData data_, BodyType type_) : 
        shape(std::move(shape_)), data(data_), type(type_) {

    }
    Body::~Body(){}
}