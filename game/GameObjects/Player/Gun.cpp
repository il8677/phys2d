#include "Gun.h"

#include "../Input.h"
#include <Engine/GameObject.h>
#include <Engine/BodyComponent.h>

#include "../Bullets/Bullet.h"

#include <phys2d/Body.h>
#include <phys2d/maths/vec2.h>

#include <iostream>

Gun::Gun(GameObject* obj, GameObject& playerObj) :
    ComponentParent(obj), player(playerObj){

}

void Gun::setup() {
    phys2d::Body* body = gameObject->getComponent<BodyComponent>()->body;
    body->layer = 0;
}

void Gun::update(float dt) {
    phys2d::Body* body = gameObject->getComponent<BodyComponent>()->body;
    phys2d::Body* playerBody = player.getComponent<BodyComponent>()->body;

    const phys2d::Vec2 mousePos(Input::getMouseX(), Input::getMouseY());
    const phys2d::Vec2 mouseVec = (mousePos - playerBody->position).normalized();

    body->position = playerBody->position + mouseVec * 3;
    body->rotation = mouseVec.getAngle();

    fireState += dt;

    if(Input::getMouseL() && fireState > fireRate){
        GameObject& b = bullet->create(playerBody->position + mouseVec * 3.5, mouseVec.getAngle());
        Bullet* bcomp = b.getComponent<Bullet>();

        fireRate = bcomp->getFireRate();

        fireState = 0;
    }
}

void Gun::setBulletPrefab(Prefab* comp){
    bullet = comp;
}
