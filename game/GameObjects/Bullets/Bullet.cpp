#include "Bullet.h"

#include <Engine/GameObject.h>
#include <Engine/BodyComponent.h>

#include "../Helper/Health.h"

Bullet::Bullet(GameObject* obj, float fireRate_, float bulletSpeed, float damage_) : Component(obj){
    fireRate = fireRate_;
    speed = bulletSpeed;
    damage = damage_;
}

int Bullet::getID() {
    return Component::getID<Bullet>();
}

void Bullet::start(){
    //gameObject.getComponent<BodyComponent>()->body->setContinuous(true);
    Body* body = gameObject->getComponent<BodyComponent>()->body;
    body->isTrigger = true;
    body->triggerCallback = [&](Body* obj, Body* other){
        Health* health = ((GameObject*)other->userData)->getComponent<Health>();

        if(health){
            health->damage(damage);
        }
        gameObject->destroy();
    };

    body->layer = 1<<1;
    body->collideWith = 1 | (1 << 3);

    setTravelVector(Vec2(body->rotation));
}

void Bullet::setTravelVector(phys2d::Vec2 travelVector_){
    travelVector = travelVector_;
    //gameObject->getComponent<BodyComponent>()->body->rotation = travelVector.getAngle();
}

void Bullet::setColliderMask(unsigned char mask){
    gameObject->getComponent<BodyComponent>()->body->collideWith = mask;
}

float Bullet::getFireRate(){
    return fireRate;
}

void Bullet::update(float dt){
    gameObject->getComponent<BodyComponent>()->body->velocity = travelVector * speed;
}