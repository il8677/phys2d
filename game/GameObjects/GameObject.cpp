#include "GameObject.h"
#include "BodyComponent.h"

GameObject GameObject::createCircle(World& world, uint32_t color, BodyData data, Vec2 pos, float r, Body::BodyType type){
    Body* b = world.createBody(new ShapeCircle(r), data, type);
    b->position = pos;
    GameObject go(std::make_unique<CircleRenderer>(r, color));
    go.addComponent<BodyComponent>(b);
    return go;
}

GameObject::GameObject(std::unique_ptr<Renderer> renderer_) : 
    renderer(std::move(renderer_)){
}

void GameObject::setup(){
    for(std::unique_ptr<Component>& component : components){
        component->setup();
    }
}

void GameObject::tick(float dt, sf::RenderWindow& window){
    renderer->render({getPosition(), getRotation()}, window);

    for(std::unique_ptr<Component>& component : components){
        component->update(dt);
    }
}

GameObject GameObject::createRect(World& world, uint32_t color, BodyData data, Vec2 pos, float hextx, float hexty, Body::BodyType type){
    Body* b = world.createBody(new ShapePoly(hextx, hexty), data, type);
    b->position = pos;
    ShapePoly* sp = (ShapePoly*)b->shape;

    GameObject go(std::make_unique<PolyRenderer>(sp->points, color));
    go.addComponent<BodyComponent>(b);

    return go;
}

Vec2 GameObject::getPosition(){
    BodyComponent* bc = getComponent<BodyComponent>();
    if(bc){
        return bc->body->position;
    }

    return Vec2(0,0);
}

Vec2 GameObject::getVelocity(){
     BodyComponent* bc = getComponent<BodyComponent>();
    if(bc){
        return bc->body->velocity;
    }

    return Vec2(0,0);
}

float GameObject::getRotation(){
     BodyComponent* bc = getComponent<BodyComponent>();
    if(bc){
        return bc->body->rotation;
    }

    return 0;
}