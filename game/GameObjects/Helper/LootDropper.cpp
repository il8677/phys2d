#include "LootDropper.h"

#include "../util/Random.h"

LootDropper::LootDropper(GameObject* obj, Prefab* lootPrefab, float probability) : ComponentParent(obj){
    prefab = lootPrefab;
    prob = probability;
}

void LootDropper::destroy(){
    if(Random::probability(prob)){
        prefab->create(gameObject->getPosition());
    }
}