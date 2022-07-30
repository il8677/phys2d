#include "Lifetime.h"

#include "../util/Random.h"
#include <Engine/GameObject.h>

Lifetime::Lifetime(GameObject* obj, float lifetime_) : ComponentParent(obj){
    lifetime = lifetime_;
}

void Lifetime::update(float dt){
    lifetime -= dt;
    if(lifetime < 0 && Random::probability(0.2)){
        gameObject->destroy();
    }
}