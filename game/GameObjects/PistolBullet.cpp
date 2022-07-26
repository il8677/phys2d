#include "PistolBullet.h"

#include "GameObject.h"
#include "BodyComponent.h"


PistolBullet::PistolBullet(GameObject* obj) : Bullet(obj, 1, 20){

}

void PistolBullet::setup(){

}

void PistolBullet::update(float dt){
    Bullet::update(dt);
}
