#pragma once
#include "maths/vec2.h"
#include "Body.h"

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

        Body* createBody(Shape* shape, BodyData data, Body::BodyType type = Body::BodyType::DYNAMIC);

        void step(float dt);

        void setGravity(Vec2 gravity);

        void reset();

        #ifdef PHYS_2D_DEBUG
        std::function<void(Contact& c)> collCB;
        #else 
        private:
        #endif

        Vec2& d_getGravity();
        const std::vector<Contact>& d_getContacts() const;
        const std::list<Body>& d_getBodies() const;

        private:
        void broadphase();
        void narrowphase();

        Vec2 gravity;

        std::list<Body> bodies; // OPTIMIZATION: better data structure?

        std::vector<SPEntry> bodiesX;
        std::vector<SPEntry> bodiesY;


        std::vector<Contact> contacts; 
    };
}