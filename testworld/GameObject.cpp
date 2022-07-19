#include "GameObject.h"

GameObject GameObject::createCircle(World& world, BodyData data, Vec2 pos, float r){
    Body* b = world.createBody(std::unique_ptr<ShapeCircle>(new ShapeCircle(r)), data);

    GameObject go(b, pos);

    go.renderable = std::make_unique<sf::CircleShape>(r);
    sf::CircleShape* s = (sf::CircleShape*)go.renderable.get();
    s->setFillColor(sf::Color(150, 50, 250));
    s->setOrigin(r, r);
}

GameObject::GameObject(Body* body_, Vec2 pos) {
    body = body;
    body->position = pos;
}

void GameObject::tick(float dt, sf::RenderWindow& window){
    window.draw(*renderable);
    renderable->setPosition(body->position.x, body->position.y);
}
