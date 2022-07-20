#pragma once
#include "maths/vec2.h"

#include <list>
#include <memory>
#include <vector>


namespace phys2d{
    struct Body;
    struct BodyData;
    class Shape;
    class Contact;

    class World{
        public:
        World(Vec2 gravity=Vec2(0,9.8f));
        ~World();

        Body* createBody(Shape* shape, BodyData data);

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

        private:
        void broadphase();
        void narrowphase();

        Vec2 gravity;

        std::list<Body> bodies; // OPTIMIZATION: better data structure?
        std::vector<Contact> contacts; 

    };
}