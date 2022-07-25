#include "Bullet.h"

Bullet::Bullet(GameObject& obj, float fireRate_) : Component(obj){
    fireRate = fireRate_;
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