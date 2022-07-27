#include "PistolBullet.h"

#include <Engine/GameObject.h>
#include <Engine/BodyComponent.h>


PistolBullet::PistolBullet(GameObject* obj) : Bullet(obj, 1, 40, 4){

}

void PistolBullet::setup(){

}

void PistolBullet::update(float dt){
    Bullet::update(dt);
}
