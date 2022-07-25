#include "Bullet.h"

#include "GameObject.h"
#include "BodyComponent.h"

Bullet::Bullet(GameObject& obj, float fireRate_, float bulletSpeed) : Component(obj){
    fireRate = fireRate_;
    speed = bulletSpeed;
}

void Bullet::start(){
    //gameObject.getComponent<BodyComponent>()->body->setContinuous(true);
    gameObject.getComponent<BodyComponent>()->body->isTrigger = true;
    gameObject.getComponent<BodyComponent>()->body->triggerCallback = [&](Body* other){
        gameObject.destroy();
    };
}

void Bullet::setTravelVector(phys2d::Vec2 travelVector_){
    travelVector = travelVector_;
}

int Bullet::getID() {
    return Component::getID<Bullet>();
}

float Bullet::getFireRate(){
    return fireRate;
}

void Bullet::update(float dt){
    gameObject.getComponent<BodyComponent>()->body->rotation = travelVector.getAngle();
    gameObject.getComponent<BodyComponent>()->body->velocity = travelVector * speed;
}