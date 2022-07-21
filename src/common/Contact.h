#pragma once
#include <phys2d/maths/vec2.h>

#include <functional>
#include <phys2d/body.h>

namespace phys2d{    
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

using namespace phys2d;
template<>
struct std::hash<Contact>{
    std::size_t operator()(Contact const& c) const noexcept{
        return std::hash<Body*>()(c.A) ^ std::hash<Body*>()(c.B);
    }
};