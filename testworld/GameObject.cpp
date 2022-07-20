#include "GameObject.h"

GameObject GameObject::createCircle(World& world, BodyData data, Vec2 pos, float r){
    Body* b = world.createBody(std::make_unique<ShapeCircle>(r), data);

    GameObject go(b, pos, std::make_unique<CircleRenderer>(r));

    return go;
}

GameObject GameObject::createPoly(World& world, BodyData data, Vec2 pos, std::initializer_list<Vec2> verts){
    Body* b = world.createBody(std::make_unique<ShapePoly>(verts), data);

    GameObject go(b, pos, std::make_unique<PolyRenderer>(verts));

    return go;
}

GameObject GameObject::createRect(World& world, BodyData data, Vec2 pos, float hextx, float hexty){
    Body* b = world.createBody(std::make_unique<ShapePoly>(hextx, hexty), data);

    ShapePoly* sp = (ShapePoly*)b->shape.get();

    GameObject go(b, pos, std::make_unique<PolyRenderer>(sp->points));
    
    return go;
}

GameObject GameObject::createSquare(World& world, BodyData data, Vec2 pos, float hext){
    return createRect(world, data, pos, hext, hext);
}


GameObject::GameObject(Body* body_, Vec2 pos, std::unique_ptr<Renderer> renderer_) : 
    renderer(std::move(renderer_)){
    body = body_;
    body->position = pos;
}

void GameObject::tick(float dt, sf::RenderWindow& window){
    renderer->render({body->position}, window);
}
