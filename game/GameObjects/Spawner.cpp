#include "Spawner.h"

#include "Suicider.h"
#include "../Input.h"

#include <random>

Spawner::Spawner(GameObject* obj, GameObject& playerObj) : ComponentParent(obj), player(playerObj) {
    
}

void Spawner::update(float dt){
    spawnState += dt;
    if(spawnState > spawnRate){
        spawnState = 0;

        Vec2 loc = {
            static_cast<float>(10+rand()%(int)(Input::getViewportX()-20)),
            static_cast<float>(10+rand()%(int)(Input::getViewportY()-20))};

        GameObject& newEnemy = enemy->create(loc);
        EnemyController* controller = newEnemy.getComponent<EnemyController>();

        controller->setTarget(&player);
    }
}

void Spawner::setEnemyPrefab(Prefab* e){
    enemy = e;
}