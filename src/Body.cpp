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

    Body::Body(Shape* shape_, BodyData data_, BodyType type_) : 
        shape(shape_), data(data_), type(type_) {

    }

    Body::Body(const Body& other) : data(other.data){
        shape = new Shape(*other.shape);
        velocity = other.velocity;
        position = other.position;
        rotation = other.rotation;

        force = other.force;

        type = other.type;
    }

    Body& Body::operator=(const Body& other){
        delete shape;
        shape = new Shape(*other.shape);
        velocity = other.velocity;
        position = other.position;
        rotation = other.rotation;

        force = other.force;

        data = other.data;

        type = other.type;

        return *this;
    }

    Body::Body(Body&& other) : data(std::move(other.data)){
        shape = other.shape;
        other.shape = nullptr;

        velocity = std::move(other.velocity);
        position = std::move(other.position);
        rotation = std::move(other.rotation);

        force = std::move(other.force);

        type = std::move(other.type);
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

        type = std::move(other.type);

        data = std::move(other.data);

    }

    Body::Body::~Body(){
        delete shape;
    }
}