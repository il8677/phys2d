#include <phys2d/World.h>
#include <phys2d/Body.h>

#include "common/Contact.h"
#include "colliders/Collision.h"

namespace phys2d{
    World::World(Vec2 gravity) : 
        gravity(gravity) {
        
    }

    World::~World()=default;

    Body* World::createBody(Shape* shape, BodyData data, Body::BodyType type){
        Body* b = &bodies.emplace_back(shape, data, type);

        broadphase.addBody(b);

        return b;
    }

    void World::setGravity(Vec2 g){
        gravity = g;
    }

    void World::reset(){
        bodies.clear();

        broadphase.clear();
    }

    void World::step(float dt){
        broadphase.run();
        narrowphase();

        for(Body& body : bodies){
            if(body.isContinuous()){
                stepCont(dt, body);
                continue;
            }

            integrateBody(dt, body);
        }
    }
    
    void World::stepCont(float dt, Body& body){
        float steps = body.velocity.magnitude() / body.shape->maxExtent;
        float maxTime = dt / steps;
        float timeExpended = 0;
        
        if(steps <= 1){
            integrateBody(dt, body);
            return;
        }
        
        int i = 0;
        // Iteratively integrate & collide
        while(timeExpended < dt){
            // Get time to step
            float itdt = maxTime;
            if(dt - timeExpended < maxTime) itdt = dt - timeExpended;

            timeExpended += itdt;

            integrateBody(itdt, body);
            
            for(Contact c : broadphase.continuousContacts[&body]){
                dispatchContact(c);

                if(c.contactCount){
                    c.resolve();
                }
            }
            i++;
        }

        return;
    }

    void World::integrateBody(float dt, Body& body){
        if(body.getType() != Body::BodyType::STATIC){
            if(body.getType() != Body::BodyType::KINEMATIC){
                body.velocity += (body.data.getMassInv() * body.force + gravity) * dt;
                body.angularVel += body.torque * body.data.getInertiaInv() * dt;
            }
                
            body.position += body.velocity * dt;
            body.rotation += body.angularVel * dt;
        }
    }

    Vec2& World::d_getGravity(){
        return gravity;
    }

    const std::vector<Contact>& World::d_getContacts() const {
        return broadphase.contacts;
    }

    const std::list<Body>& World::d_getBodies() const{
        return bodies;
    }

    void World::narrowphase(){
        for(Contact& c : broadphase.contacts){
            dispatchContact(c);

            if(c.contactCount){
                c.resolve();
            }
        }
    }
}
