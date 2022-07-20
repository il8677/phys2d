#include "GameObject.h"

GameObject GameObject::createCircle(World& world, BodyData data, Vec2 pos, float r){
    Body* b = world.createBody(std::unique_ptr<ShapeCircle>(new ShapeCircle(r)), data);

    GameObject go(b, pos);

    go.renderable = std::make_unique<sf::CircleShape>(r);
    sf::CircleShape* s = (sf::CircleShape*)go.renderable.get();
    s->setFillColor(sf::Color(150, 50, 250));
    s->setOrigin(r, r);

    return go;
}

GameObject GameObject::createPoly(World& world, BodyData data, Vec2 pos, std::initializer_list<Vec2> verts){
    Body* b = world.createBody(std::unique_ptr<ShapePoly>(new ShapePoly(verts)), data);

    GameObject go(b, pos);

    go.renderable = std::make_unique<sf::ConvexShape>(verts.size());
    sf::ConvexShape* s = (sf::ConvexShape*)go.renderable.get();

    int i = 0;
    for(auto it = verts.begin(); it != verts.end(); it++){
        s->setPoint(i, sf::Vector2f(it->x, it->y));
        i++;
    }
    
    s->setFillColor(sf::Color(56, 94, 156));

    return go;
}

GameObject GameObject::createRect(World& world, BodyData data, Vec2 pos, float hextx, float hexty){
    Body* b = world.createBody(std::unique_ptr<ShapePoly>(new ShapePoly(hextx, hexty)), data);

    ShapePoly* sp = (ShapePoly*)b->shape.get();

    GameObject go(b, pos);
    
    go.renderable = std::make_unique<sf::ConvexShape>(sp->points.size());
    sf::ConvexShape* s = (sf::ConvexShape*)go.renderable.get();

    int i = 0;
    for(auto it = sp->points.begin(); it != sp->points.end(); it++){
        s->setPoint(i, sf::Vector2f(it->x, it->y));
        i++;
    }

    s->setFillColor(sf::Color(74, 186, 48));

    return go;
}

GameObject GameObject::createSquare(World& world, BodyData data, Vec2 pos, float hext){
    return createRect(world, data, pos, hext, hext);
}


GameObject::GameObject(Body* body_, Vec2 pos) {
    body = body_;
    body->position = pos;
}

void GameObject::tick(float dt, sf::RenderWindow& window){
    window.draw(*renderable);
    renderable->setPosition(body->position.x, body->position.y);
}
