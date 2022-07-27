#include "Player.h"

#include "Gun.h"

#include "../Input.h"
#include <Engine/BodyComponent.h>
#include <Engine/GameObject.h>

#include <phys2d/World.h>
#include <phys2d/colliders/Shape.h>

#include <SFML/Window/Event.hpp>

using namespace phys2d;

Player::Player(GameObject* obj, Gun* gun_) : ComponentParent(obj) {
    gun = gun_;
}

void Player::update(float dt){
    Body* body = gameObject->getComponent<BodyComponent>()->body;

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
}

void Player::setBulletPrefab(Prefab* prefab){
    gun->setBulletPrefab(prefab);
}