#pragma once
#include "Body.h"
#include "maths/vec2.h"
#include "../../src/maths/Broadphase.h"

#include <list>
#include <memory>
#include <vector>
#include <set>
#include <functional>


namespace phys2d{
    struct Body;
    struct BodyData;
    struct SPEntry;
    class Shape;
    class Contact;

    class World{
        public:
        World(Vec2 gravity=Vec2(0,9.8f));
        ~World();

        // Creates a new body
        Body* createBody(Shape* shape, BodyData data, Body::BodyType type = Body::BodyType::DYNAMIC);
        // Creates a new body copied from provided body
        Body* createBody(Body* b);
        void destroyBody(Body* body);

        void clear();

        void step(float dt);

        void setGravity(Vec2 gravity);

        void reset();

        // Debug functions
        #ifdef PHYS_2D_DEBUG
        std::function<void(Contact& c)> collCB;
        #else 
        private:
        #endif

        Vec2& d_getGravity();
        const std::vector<Contact>& d_getContacts() const;
        const std::list<Body>& d_getBodies() const;

        private:
        // Step a continuous body
        void stepCont(float dt, Body& body);

        void integrateBody(float dt, Body& body);

        void narrowphase();

        Vec2 gravity;
        std::list<Body> bodies; 
        Broadphase broadphase;
    };
}