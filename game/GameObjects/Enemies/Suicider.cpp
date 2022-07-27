#include "Suicider.h"

#include <Engine/GameObject.h>

#include "../Helper/Health.h"
#include "../Player/Player.h"

#include <phys2d/Body.h>
#include <phys2d/maths/vec2.h>

using namespace phys2d;

Suicider::Suicider(GameObject* obj) : EnemyController(obj){

}

Component* Suicider::clone(GameObject* newObj) {
    Component* n = new Suicider(*this);
    n->setGameObject(newObj);
    
    return n;
}

void Suicider::start(){
    Body* b = gameObject->getComponent<BodyComponent>()->body;
    b->triggerCallback = [&](Body* obj, Body* other){
        GameObject* otherObj = (GameObject*)other->userData;
        if(otherObj->getComponent<Player>()){
            if(Health* h = target->getComponent<Health>()){
                h->damage(3);
            }

            gameObject->destroy();
        }
    };
}

void Suicider::update(float dt){
    Body* targetBody = target->getComponent<BodyComponent>()->body;
    Body* thisBody = gameObject->getComponent<BodyComponent>()->body;

    Vec2 dir =  targetBody->position - thisBody->position;

    thisBody->velocity += dir * speed * dt;
    if(thisBody->velocity.magnitudeSq() > 4000) thisBody->velocity *= 0.8f;
}