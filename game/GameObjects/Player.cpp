#include "Player.h"

#include "../Input.h"

#include <phys2d/World.h>
#include <phys2d/colliders/Shape.h>

#include <SFML/Window/Event.hpp>

using namespace phys2d;

Player::Player(World& world, Vec2 pos) : 
    GameObject(
        world.createBody(new ShapeCircle(1), BodyData(1), Body::BodyType::KINEMATIC), 
        pos, 
        std::make_unique<CircleRenderer>(1, 0x76B041FF)){
    
}

void Player::tick(float dt, sf::RenderWindow& window){
    body->velocity = {0,0};
    if(Input::getKeyState(sf::Keyboard::Key::A)){
        body->velocity.x = -moveSpeed;
    }
    if(Input::getKeyState(sf::Keyboard::Key::D)){
        body->velocity.x = moveSpeed;
    }    
    if(Input::getKeyState(sf::Keyboard::Key::W)){
        body->velocity.y = -moveSpeed;
    }    
    if(Input::getKeyState(sf::Keyboard::Key::S)){
        body->velocity.y = moveSpeed;
    }
    GameObject::tick(dt, window);
}