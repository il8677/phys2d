#include "GameObject.h"

GameObject::GameObject(Body* body_, Vec2 pos, std::unique_ptr<Renderer> renderer_) : 
    renderer(std::move(renderer_)){
    body = body_;
    body->position = pos;
}

void GameObject::tick(float dt, sf::RenderWindow& window){
    renderer->render({body->position, body->rotation}, window);
}
