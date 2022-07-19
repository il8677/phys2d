#pragma once
#include "maths/vec2.h"
#include "maths/rotation.h"
#include "colliders/shape.h"

#include <memory>

namespace phys2d{
    struct Vec2;

    struct BodyData{
        BodyData(float mass, float restitution=0.1f);

        void setMass(float mass);

        float getMass();
        float getMassInv();

        private:
        float mass;
        float massinv;

        float restitution;
    };

    struct Body{
        enum BodyType { STATIC, DYNAMIC, KINEMATIC};

        Body(std::unique_ptr<Shape> shape, BodyData data, BodyType type=DYNAMIC);

        std::unique_ptr<Shape> shape;

        Vec2 velocity;

        Vec2 position;
        Rotation rotation;

        Vec2 force;

        BodyData data;
        
        BodyType type;
    };
}