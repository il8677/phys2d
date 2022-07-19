#include "Contact.h"

#include <phys2d/Body.h>

#include <cmath>

namespace phys2d{
    Contact::Contact(Body* A_, Body* B_) : 
        A(A_), B(B_) {

    }

    void Contact::resolve(){
        updateVelocities();
        fixError();
    }

    void Contact::updateVelocities(){
        Vec2 rv = B->velocity - A->velocity;

        float sN = rv.dot(normal);

        if(std::abs(sN) <= 1e-7) return;

        float r = std::min(A->data.restitution, B->data.restitution);

        float mImpulse = (-(1+r) * sN) / (A->data.getMassInv() + B->data.getMassInv());
        
        Vec2 impulse = mImpulse * normal;

        // Apply scaled impulse based on body mass
        // Have to apply directly, applying a force would be affected by delta time
        A->velocity -= A->data.getMassInv() * impulse;
        B->velocity += B->data.getMassInv() * impulse;
    }

    // PAPERNOTE: Floating point precision error solved with "Linear projection"
    void Contact::fixError(){
        const float correction = 0.2f;

        float mWeightedPen = pen / ((A->data.getMassInv() + B->data.getMassInv()));

        Vec2 correctionVec = mWeightedPen * correction * normal;

        A->position -= A->data.getMassInv() * correctionVec;
        B->position += B->data.getMassInv() * correctionVec;
    }
}