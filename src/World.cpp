#include <phys2d/World.h>
#include <phys2d/Body.h>

#include "common/Contact.h"
#include "colliders/Collision.h"
#include "maths/algs.h"

#include <unordered_set>

namespace phys2d{
    World::World(Vec2 gravity) : 
        gravity(gravity) {
        
    }

    World::~World()=default;

    Body* World::createBody(Shape* shape, BodyData data, Body::BodyType type){
        Body* b = &bodies.emplace_back(shape, data, type);

        insertInPlace(bodiesX, SPEntry(b,0));
        insertInPlace(bodiesY, SPEntry(b,1));

        return b;
    }

    void World::setGravity(Vec2 g){
        gravity = g;
    }

    void World::reset(){
        bodies.clear();

        bodiesX.clear();
        bodiesY.clear();

        contacts.clear();
    }

    void World::step(float dt){
        contacts.clear();

        broadphase();
        narrowphase();

        for(Body& body : bodies){
            if(body.getType() != Body::BodyType::STATIC){
                if(body.getType() != Body::BodyType::KINEMATIC){
                    body.velocity += (body.data.getMassInv() * body.force + gravity) * dt;
                    body.angularVel += body.torque * body.data.getInertiaInv() * dt;
                }
                    
                body.position += body.velocity * dt;
                body.rotation += body.angularVel * dt;
            }
        }
    }

    Vec2& World::d_getGravity(){
        return gravity;
    }

    const std::vector<Contact>& World::d_getContacts() const {
        return contacts;
    }

    const std::list<Body>& World::d_getBodies() const{
        return bodies;
    }

    void World::broadphase(){
        insertionSort(bodiesX);
        insertionSort(bodiesY);

        std::vector<SPEntry> current;
        current.reserve(bodiesX.size());

        std::unordered_set<Contact> possibleX;
        std::unordered_set<Contact> possibleY;

        possibleX.reserve(bodies.size()/2);
        possibleY.reserve(bodies.size()/2);

        for(SPEntry& entry : bodiesX){
            current.erase(std::remove_if(
                current.begin(), current.end(), [&](const SPEntry& e){
                    return e.isBehind(entry);
                }), current.end());

            for(auto it = current.begin(); it != current.end(); it++){
                contacts.emplace_back(entry.body, it->body);
            }

            current.push_back(entry);
        }
        return;
        current.clear();

        for(SPEntry& entry : bodiesY){
            current.erase(std::remove_if(
                current.begin(), current.end(), [&](const SPEntry& e){
                    return e.isBehind(entry);
                }), current.end());
            for(auto it = current.begin(); it != current.end(); it++){
                possibleY.emplace(entry.body, it->body);
            }

            current.push_back(entry);
        }

        /*
        for(auto A = bodies.begin(); A != bodies.end(); A++){
            for(auto B = std::next(A); B != bodies.end(); B++){
                contacts.emplace_back(&*A, &*B);
            }
        }*/
    }

    void World::narrowphase(){
        for(Contact& c : contacts){
            dispatchContact(c);

            if(c.contactCount){
                c.resolve();
            }
        }
    }
}
