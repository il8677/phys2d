#include "Loot.h"
#include "../Player/Player.h"

#include <Engine/BodyComponent.h>

Loot::Loot(GameObject* obj, Prefab* bullet) : ComponentParent(obj){
    bulletPrefab = bullet;
}

void Loot::start(){
    gameObject->getComponent<BodyComponent>()->body->triggerCallback = [&](Body* obj, Body* other){
        GameObject* otherObj = (GameObject*)other->userData;

        if(Player* p = otherObj->getComponent<Player>()){
            p->setBulletPrefab(bulletPrefab);

            gameObject->destroy();
        }
    };
}