#include "Bullet.h"

Bullet::Bullet(GameObject& obj) : Component(obj){

}

void Bullet::setTravelVector(phys2d::Vec2 travelVector_){
    travelVector = travelVector_;
}

int Bullet::getID() {
    return Component::getID<Bullet>();
}
