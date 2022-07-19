#include <phys2d/world.h>
#include <phys2d/body.h>

namespace phys2d{
    World::World(Vec2 gravity) : gravity(gravity){
        
    }

    Body* World::createBody(std::unique_ptr<Shape> shape, BodyData data){
        return &bodies.emplace_back(std::move(shape), data);
    }

    void World::step(float dt){
        for(Body& body : bodies){
        if(body.type != Body::BodyType::STATIC){
                if(body.type != Body::BodyType::KINEMATIC)
                    body.velocity += (body.force + gravity) * dt;
                    
                body.position += body.velocity * dt;
                body.force.zero();
            }
        }
    }
}