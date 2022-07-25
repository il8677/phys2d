#include "PistolBullet.h"

#include "GameObject.h"
#include "BodyComponent.h"


PistolBullet::PistolBullet(GameObject& obj) : Bullet(obj, 1){

}

void PistolBullet::setup(){

}

void PistolBullet::update(float dt){
    gameObject.getComponent<BodyComponent>()->body->rotation = travelVector.getAngle();
    gameObject.getComponent<BodyComponent>()->body->velocity = travelVector * speed;
}
