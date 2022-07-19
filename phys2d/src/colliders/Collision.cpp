#include "Collision.h"
#include <phys2d/Body.h>

#include <functional>

namespace phys2d{
    void dispatchContact(Contact& contact){
        static std::function<void(Contact&)> resolves[2][2] = {
            {CircleCircle, CirclePoly},
            {CirclePoly, PolyPoly}};

        Body* A = contact.A;
        Body* B = contact.B;

        resolves[A->shape->type][B->shape->type](contact);
    }

    void CircleCircle(Contact& contact){
        Body* bA = contact.A;
        Body* bB = contact.B;

        ShapeCircle* A = (ShapeCircle*)bA->shape.get();
        ShapeCircle* B = (ShapeCircle*)bB->shape.get();

        Vec2 colNormal = bB->position - bA->position;
        float dist = colNormal.magnitude();
        float totalRadius = A->radius + B->radius;

        if(dist > totalRadius){
            contact.inContact = false;
            return;
        }

        contact.inContact = true;
        contact.pen = totalRadius - dist;
        contact.normal = colNormal.normalized();
        contact.contactPoint = contact.normal * A->radius + bA->position;
    }

    void CirclePoly(Contact& contact){
        Body* bA;
        Body* bB;

        if(contact.A->shape->type == Shape::Type::CIRCLE){
            bA = contact.A;
            bA = contact.B;
        }else{
            bA = contact.B;
            bB = contact.A;
        }

        ShapeCircle* A = (ShapeCircle*)bA->shape.get();
        ShapeCircle* B = (ShapeCircle*)bB->shape.get();
    }

    void PolyPoly(Contact& contact){

    }

}