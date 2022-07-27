#include "Spawner.h"

#include "Suicider.h"
#include "../Input.h"

#include <random>

Spawner::Spawner(GameObject* obj, GameObject* playerObj) : ComponentParent(obj), player(playerObj) {
    
}

void Spawner::update(float dt){
    spawnState += dt;
    if(spawnState > spawnRate){
        spawnState = 0;
        spawns++;

        Vec2 loc = {
            static_cast<float>(10+rand()%(int)(Input::getViewportX()-20)),
            static_cast<float>(10+rand()%(int)(Input::getViewportY()-20))};

        int nextEnemyIndex = (rand()%(spawns/4)) % enemies.size();

        GameObject& newEnemy = enemies[nextEnemyIndex]->create(loc);
        EnemyController* controller = newEnemy.getComponent<EnemyController>();

        controller->setTarget(player);
    }
}

void Spawner::addEnemyPrefab(Prefab* e){
    enemies.push_back(e);
}