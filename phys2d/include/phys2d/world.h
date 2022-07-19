#pragma once
#include "maths/vec2.h"
#include <list>
#include <memory>


namespace phys2d{
    struct Body;
    struct BodyData;
    class Shape;
    class Contact;

    class World{
        public:
        World(Vec2 gravity=Vec2(0,9.8f));

        Body* createBody(std::unique_ptr<Shape> shape, BodyData data);

        void step(float dt);

        private:
        Vec2 gravity;

        std::list<Body> bodies;
    };
}