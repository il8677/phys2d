#include "Bullet.h"

#include "GameObject.h"
#include "BodyComponent.h"
#include "Health.h"

Bullet::Bullet(GameObject* obj, float fireRate_, float bulletSpeed) : ComponentParent(obj){
    fireRate = fireRate_;
    speed = bulletSpeed;
}

void Bullet::start(){
    //gameObject.getComponent<BodyComponent>()->body->setContinuous(true);
    gameObject->getComponent<BodyComponent>()->body->isTrigger = true;
    gameObject->getComponent<BodyComponent>()->body->triggerCallback = [&](Body* obj, Body* other){
        Health* health = ((GameObject*)other->userData)->getComponent<Health>();

        if(health){
            health->damage(5);
        }
        gameObject->destroy();
    };
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