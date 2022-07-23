#include "GameObject.h"

GameObject GameObject::createCircle(World& world, BodyData data, Vec2 pos, float r, Body::BodyType type){
    Body* b = world.createBody(new ShapeCircle(r), data, type);

    GameObject go(b, pos, std::make_unique<CircleRenderer>(r));

    return go;
}

GameObject GameObject::createPoly(World& world, BodyData data, Vec2 pos, std::initializer_list<Vec2> verts, Body::BodyType type){
    Body* b = world.createBody(new ShapePoly(verts), data, type);

    GameObject go(b, pos, std::make_unique<PolyRenderer>(verts));

    return go;
}

GameObject GameObject::createRect(World& world, BodyData data, Vec2 pos, float hextx, float hexty, Body::BodyType type){
    Body* b = world.createBody(new ShapePoly(hextx, hexty), data, type);

    ShapePoly* sp = (ShapePoly*)b->shape;

    GameObject go(b, pos, std::make_unique<PolyRenderer>(sp->points));
    
    return go;
}

GameObject GameObject::createSquare(World& world, BodyData data, Vec2 pos, float hext, Body::BodyType type){
    return createRect(world, data, pos, hext, hext, type);
}


GameObject::GameObject(Body* body_, Vec2 pos, std::unique_ptr<Renderer> renderer_) : 
    renderer(std::move(renderer_)){
    body = body_;
    body->position = pos;
}

void GameObject::tick(float dt, sf::RenderWindow& window){
    renderer->render({body->position, body->rotation}, window);
}
