#include "Bullet.h"

#include "GameObject.h"
#include "BodyComponent.h"
#include "Health.h"

Bullet::Bullet(GameObject* obj, float fireRate_, float bulletSpeed, float damage_) : ComponentParent(obj){
    fireRate = fireRate_;
    speed = bulletSpeed;
    damage = damage_;
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
    body->collideWith = 1;
}

void Bullet::setTravelVector(phys2d::Vec2 travelVector_){
    travelVector = travelVector_;
}

float Bullet::getFireRate(){
    return fireRate;
}

void Bullet::update(float dt){
    gameObject->getComponent<BodyComponent>()->body->rotation = travelVector.getAngle();
    gameObject->getComponent<BodyComponent>()->body->velocity = travelVector * speed;
}