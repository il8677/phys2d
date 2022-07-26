#include "Spawner.h"

#include "Suicider.h"

Spawner::Spawner(GameObject* obj, GameObject& playerObj) : ComponentParent(obj), player(playerObj) {
    
}

void Spawner::update(float dt){
    spawnState += dt;
    if(spawnState > spawnRate){
        spawnState = 0;

        GameObject& newEnemy = enemy->create({50,50});
        EnemyController* controller = newEnemy.getComponent<EnemyController>();

        controller->setTarget(&player);
    }
}

void Spawner::setEnemyPrefab(Prefab* e){
    enemy = e;
}