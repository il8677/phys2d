#include "Contact.h"

#include <phys2d/Body.h>

#include <cmath>

namespace phys2d{
    Contact::Contact(Body* A_, Body* B_) {
        A = A_;
        B = B_;

        continuous = A->isContinuous() || B->isContinuous();
    }

    void Contact::resolve(){
        if(A->triggerCallback)
            A->triggerCallback(B);
        
        if(A->triggerCallback) 
            B->triggerCallback(A);

        if(A->isTrigger || B->isTrigger) return;

        updateVelocities();
        fixError();
    }

    void Contact::updateVelocities(){
        float r = std::min(A->data.restitution, B->data.restitution);

        for(int i = 0; i < contactCount; i++){
            Vec2 ra = contactPoints[i] - A->position;
            Vec2 rb = contactPoints[i] - B->position;

            Vec2 rv = B->velocity - A->velocity + rb.cross(B->angularVel) - ra.cross(A->angularVel);

            float sN = rv.dot(normal);

            if(std::abs(sN) <= 1e-7) return;

            float raN = ra.cross(normal);
            float rbN = rb.cross(normal);

            float invMSum = A->data.getMassInv() + B->data.getMassInv();
            invMSum += raN * raN * A->data.getInertiaInv() + rbN * rbN * A->data.getInertiaInv();

            float impulse = -(1.0f+r) * sN;
            impulse /= invMSum;
            impulse /= (float)contactCount;

            Vec2 impulseV = impulse * normal;

            A->velocity -= A->data.getMassInv() * impulseV;
            A->angularVel -= A->data.getInertiaInv() * ra.cross(impulseV);

            B->velocity += B->data.getMassInv() * impulseV;
            B->angularVel += B->data.getInertiaInv() * rb.cross(impulseV);

            // Friction

            Vec2 t = rv - normal * rv.dot(normal);
            t.normalize();

            float jt = -rv.dot(t) / invMSum / (float)contactCount;

            Vec2 tanJ;
            if(std::abs(jt) < impulse * 0.01f)
                tanJ = -t * jt;
            else
                tanJ = t * jt * 0.01f;

            A->velocity -= A->data.getMassInv() * tanJ;
            A->angularVel -= A->data.getInertiaInv() * ra.cross(tanJ);

            B->velocity += B->data.getMassInv() * tanJ;
            B->angularVel += B->data.getInertiaInv() * rb.cross(tanJ);
            
        }
    }

    void Contact::fixError(){
        const float correction = 0.4f;

        float mWeightedPen = pen / ((A->data.getMassInv() + B->data.getMassInv()));

        Vec2 correctionVec = mWeightedPen * correction * normal;

        A->position -= A->data.getMassInv() * correctionVec;
        B->position += B->data.getMassInv() * correctionVec;
    }

    bool operator==(const Contact& A, const Contact& B){
        return (A.A == B.A && A.B == B.B);
    }

    bool operator<(const Contact& A, const Contact& B){
        return std::hash<Contact>()(A) < std::hash<Contact>()(B);
    }
}
