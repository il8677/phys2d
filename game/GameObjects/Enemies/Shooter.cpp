#include "Shooter.h"

#include <Engine/GameObject.h>
#include <Engine/BodyComponent.h>

#include "../Input.h"
#include "../util/Random.h"

#include "../Bullets/Bullet.h"

#include <phys2d/Body.h>
#include <phys2d/maths/vec2.h>


Shooter::Shooter(GameObject* obj) :
    EnemyController(obj){

}

Component* Shooter::clone(GameObject* newObj) {
    Component* n = new Shooter(*this);
    n->setGameObject(newObj);
    
    return n;
}

void Shooter::update(float dt) {
    timer += dt;

    shoot(dt);
    movement(dt);
}

void Shooter::setBulletPrefab(Prefab* comp){
    bullet = comp;
}

void Shooter::shoot(float dt){
    phys2d::Body* body = gameObject->getComponent<BodyComponent>()->body;

    fireState += dt;

    if(fireState > fireRate){
        phys2d::Body* playerBody = target->getComponent<BodyComponent>()->body;

        const phys2d::Vec2 targetVec = (playerBody->position - body->position + Random::randVec(Vec2(-5,-5), Vec2(5,5))).normalized();

        GameObject& b = bullet->create(body->position + targetVec * 5, targetVec.getAngle());
        Bullet* bcomp = b.getComponent<Bullet>();
        bcomp->setColliderMask(1);

        fireRate = bcomp->getFireRate();

        fireState = 0;
    }
}

void Shooter::movement(float dt){
    phys2d::Body* body = gameObject->getComponent<BodyComponent>()->body;

    body->velocity = sin(timer/3) * Vec2(10, 0) + cos(timer/3) * Vec2(0, 10);
}