#include "EnemyController.h"

#include <Engine/Component.h>
#include <Engine/GameObject.h>

using namespace phys2d;

EnemyController::EnemyController(GameObject* obj) : Component(obj){

}

int EnemyController::getID(){
    return Component::getID<EnemyController>();
}

void EnemyController::setTarget(GameObject* target_){
    if(target_->getComponent<BodyComponent>()){
        target = target_; // Not safe if not player
    }
}