#pragma once
#include "maths/vec2.h"
#include "maths/Rotation.h"
#include "colliders/Shape.h"

#include <memory>
#include <functional>

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
        Body();

        Body& operator=(const Body& other);

        Body(Body&& other);
        Body& operator=(Body&& other);

        ~Body();

        Shape* shape = nullptr;

        // layers
        unsigned char layer=1;
        bool isTrigger = false;
        std::function<void(Body* other)> triggerCallback;

        void* userData=nullptr;

        bool doDestroy=false;

        // physical values
        Vec2 force;
        Vec2 velocity;
        Vec2 position;

        Rotation angularVel;
        Rotation torque;
        Rotation rotation;

        BodyData data;

        BodyType getType() const;
        void setType(BodyType type);

        void setContinuous(bool continuous);
        bool isContinuous();

        private:
        bool continuous = false;
        BodyType type;
    };
}