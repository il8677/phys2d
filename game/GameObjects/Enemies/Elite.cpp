#include "Elite.h"

#include "../util/Random.h"

#include <Engine/BodyComponent.h>

#include <phys2d/Body.h>

using namespace phys2d;

Elite::Elite(GameObject* obj) : Shooter(obj){
    target = Random::randVecInViewport();
}

Component* Elite::clone(GameObject* newObj){
    Component* n = new Elite(*this);
    n->setGameObject(newObj);

    return n;
}

void Elite::movement(float dt){
    Body* body = gameObject->getComponent<BodyComponent>()->body;

    Vec2 targetVec = target - body->position;

    float dist = targetVec.magnitudeSq();

    if(body->velocity.magnitudeSq() > 3000) body->velocity *= 0.75f;

    if(dist < 50){
        target = Random::randVecInViewport();
    }else if (targetVec.dot(body->velocity) < 10){
        body->velocity += targetVec*0.5f;
    }
}