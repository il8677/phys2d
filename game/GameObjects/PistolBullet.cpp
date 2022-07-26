#include "PistolBullet.h"

#include "GameObject.h"
#include "BodyComponent.h"


PistolBullet::PistolBullet(GameObject* obj) : Bullet(obj, 1, 40){

}

void PistolBullet::setup(){

}

void PistolBullet::update(float dt){
    Bullet::update(dt);
}
