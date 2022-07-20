#include <phys2d/World.h>
#include <phys2d/Body.h>
#include "common/Contact.h"
#include "colliders/Collision.h"

namespace phys2d{
    World::World(Vec2 gravity) : gravity(gravity){
        
    }

    World::~World()=default;

    Body* World::createBody(std::unique_ptr<Shape> shape, BodyData data){
        return &bodies.emplace_back(std::move(shape), data);
    }

    void World::setGravity(Vec2 g){
        gravity = g;
    }

    void World::reset(){
        bodies.clear();
        contacts.clear();
    }

    void World::step(float dt){
        contacts.clear();

        broadphase();
        narrowphase();

        for(Body& body : bodies){
            if(body.type != Body::BodyType::STATIC){
                if(body.type != Body::BodyType::KINEMATIC)
                    body.velocity += (body.force + gravity) * dt;
                    
                body.position += body.velocity * dt;
                body.force.zero();
            }
        }
    }

    Vec2& World::d_getGravity(){
        return gravity;
    }

    const std::vector<Contact>& World::d_getContacts() const {
        return contacts;
    }


    void World::broadphase(){
        contacts.reserve(bodies.size());

        for(auto A = bodies.begin(); A != bodies.end(); A++){
            for(auto B = std::next(A); B != bodies.end(); B++){
                contacts.emplace_back(&*A, &*B);
            }
        }
    }

    void World::narrowphase(){
        for(Contact& c : contacts){
            dispatchContact(c);

            if(c.inContact){
                c.resolve();
            }
        }
    }
}