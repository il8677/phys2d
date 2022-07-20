#pragma once
#include <phys2d/maths/vec2.h>

namespace phys2d{
    struct Body;
    
    struct Contact{
        Body* A;
        Body* B;

        bool inContact;
        float pen;
        Vec2 normal;
        Vec2 contactPoint;

        Contact(Body* A, Body* B);

        void resolve();

        friend bool operator==(const Contact& A, const Contact& B);

        private:
        void updateVelocities();
        void fixError();
    };
}