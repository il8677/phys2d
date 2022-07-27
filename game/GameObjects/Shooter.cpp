#include "Shooter.h"

#include "../Input.h"
#include "GameObject.h"
#include "BodyComponent.h"

#include "Bullet.h"
#include "PistolBullet.h"

#include <phys2d/Body.h>
#include <phys2d/maths/vec2.h>

#include <random>

Shooter::Shooter(GameObject* obj) :
    EnemyController(obj){

}

Component* Shooter::clone(GameObject* newObj) const {
    Component* n = new Shooter(*this);
    n->setGameObject(newObj);
    
    return n;
}

void Shooter::setup() {

}

void Shooter::update(float dt) {
    phys2d::Body* body = gameObject->getComponent<BodyComponent>()->body;
    fireState += dt;

    timer += dt;

    if(fireState > fireRate){
        phys2d::Body* playerBody = target->getComponent<BodyComponent>()->body;

        const phys2d::Vec2 targetVec = (playerBody->position - body->position + Vec2(1.5f, 1.5f) * ((rand()%10)-5)).normalized();

        GameObject& b = bullet->create(body->position + targetVec * 4);
        Bullet* bcomp = b.getComponent<Bullet>();
        bcomp->setTravelVector(targetVec);

        fireRate = bcomp->getFireRate();

        fireState = 0;
    }

    body->velocity = sin(timer/3) * Vec2(10, 0) + cos(timer/3) * Vec2(0, 10);
}

void Shooter::setBulletPrefab(Prefab* comp){
    bullet = comp;
}
