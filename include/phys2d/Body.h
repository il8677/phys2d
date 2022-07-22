#pragma once
#include "maths/vec2.h"
#include "maths/Rotation.h"
#include "colliders/Shape.h"

#include <memory>

namespace phys2d{
    struct Vec2;

    struct BodyData{
        BodyData(float mass, float restitution=0.1f);

        void setMass(float mass);

        float getMass();
        float getMassInv();

        float getInertia();
        float getInertiaInv();

        float restitution;

        private:
        float inertia;
        float inertiainv;
        float mass;
        float massinv;
    };

    struct Body{
        enum BodyType { STATIC, DYNAMIC, KINEMATIC};

        Body(Shape* shape, BodyData data, BodyType type=DYNAMIC);
        Body(const Body& other);
        Body& operator=(const Body& other);

        Body(Body&& other);
        Body& operator=(Body&& other);

        ~Body();

        Shape* shape = nullptr;

        Vec2 force;
        Vec2 velocity;
        Vec2 position;

        Rotation rotation;

        Rotation angularVel;
        Rotation torque;

        BodyData data;
        
        BodyType type;
    };
}