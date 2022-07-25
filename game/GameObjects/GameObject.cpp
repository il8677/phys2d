#include "GameObject.h"

GameObject::GameObject(Body* body_, Vec2 pos, std::unique_ptr<Renderer> renderer_) : 
    renderer(std::move(renderer_)){
    body = body_;
    body->position = pos;
}

void GameObject::tick(float dt, sf::RenderWindow& window){
    renderer->render({body->position, body->rotation}, window);
}

std::unique_ptr<GameObject> GameObject::createRect(World& world, uint32_t color, BodyData data, Vec2 pos, float hextx, float hexty, Body::BodyType type){
    Body* b = world.createBody(new ShapePoly(hextx, hexty), data, type);

    ShapePoly* sp = (ShapePoly*)b->shape;

    return std::make_unique<GameObject>(b, pos, std::make_unique<PolyRenderer>(sp->points, color));
}
