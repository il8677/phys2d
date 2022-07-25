#include <phys2d/Body.h>

namespace phys2d{
    BodyData::BodyData(float mass_, float restitution_) : 
        restitution(restitution_) {
        setMass(mass_);
    }

    void BodyData::setMass(float mass_){
        mass = mass_;
        if(mass!=0){
            massinv = 1/mass_;
            inertiainv = 1/(mass_*2);
        }else{
            massinv = 0;
            inertiainv = 0;
        }
        inertia = 2*mass_;
    }

    float BodyData::getMass(){
        return mass;
    }

    float BodyData::getMassInv(){
        return massinv;
    }

    float BodyData::getInertia(){
        return inertia;
    }

    float BodyData::getInertiaInv(){
        return inertiainv;
    }

    Body::Body(Shape* shape_, BodyData data_, BodyType type_) : 
        shape(shape_), data(data_) {
        setType(type_);
    }

    Body::Body(const Body& other) : data(other.data){
        shape = new Shape(*other.shape);
        velocity = other.velocity;
        position = other.position;
        rotation = other.rotation;

        force = other.force;

        setType(other.type);

        isTrigger = other.isTrigger;
        triggerCallback = other.triggerCallback;
        doDestroy = other.doDestroy;
    }

    Body& Body::operator=(const Body& other){
        delete shape;
        shape = new Shape(*other.shape);
        velocity = other.velocity;
        position = other.position;
        rotation = other.rotation;

        force = other.force;

        data = other.data;

        setType(other.type);

        doDestroy = other.doDestroy;
        triggerCallback = other.triggerCallback;
        isTrigger = other.isTrigger;

        return *this;
    }

    Body::Body(Body&& other) : data(std::move(other.data)){
        shape = other.shape;
        other.shape = nullptr;

        velocity = std::move(other.velocity);
        position = std::move(other.position);
        rotation = std::move(other.rotation);

        force = std::move(other.force);

        setType(other.type);

        isTrigger = other.isTrigger;
        doDestroy = other.doDestroy;
        triggerCallback = std::move(other.triggerCallback);
    }

    Body& Body::operator=(Body&& other){
        if(this == &other){
            return *this;
        }

        delete shape;

        shape = other.shape;
        other.shape = nullptr;

        velocity = std::move(other.velocity);
        position = std::move(other.position);
        rotation = std::move(other.rotation);

        force = std::move(other.force);

        setType(other.type);

        data = std::move(other.data);
        isTrigger = other.isTrigger;
        doDestroy = other.doDestroy;
        triggerCallback = std::move(other.triggerCallback);
        return *this;
    }

    Body::Body::~Body(){
        delete shape;
    }

    Body::BodyType Body::getType() const{
        return type;
    }

    void Body::setType(Body::BodyType type_){
        type = type_;

        if(type == Body::BodyType::STATIC){
            data.setMass(0);
            data.restitution = 1;
        }
    }

    void Body::setContinuous(bool continuous_){
        continuous = continuous_;

        if(continuous){
        }
    }

    bool Body::isContinuous(){
        return continuous;
    }
}