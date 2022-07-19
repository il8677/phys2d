#include "Contact.h"

#include <phys2d/Body.h>

namespace phys2d{
    Contact::Contact(Body* A_, Body* B_) : 
        A(A_), B(B_) {

    }

    void Contact::resolve(){
        Vec2 rv = B->velocity - A->velocity;

        float sN = rv.dot(normal);

        if(!sN) return;

        float r = std::min(A->data.restitution, B->data.restitution);

        float mImpulse = (-(1+r) * sN) / (A->data.getMassInv() + B->data.getMassInv());
        
        Vec2 impulse = mImpulse * normal;

        // Apply scaled impulse based on body mass
        A->velocity -= A->data.getMassInv() * impulse;
        B->velocity += B->data.getMassInv() * impulse;
    }
}