#include "Spawner.h"

#include "../Input.h"

#include "../util/Random.h"
#include "../Enemies/EnemyController.h"

#include <algorithm>

Spawner::Spawner(GameObject* obj, GameObject* playerObj) : ComponentParent(obj), player(playerObj) {
    
}

void Spawner::update(float dt){
    spawnState += dt;
    if(spawnState > spawnRate){
        spawnState = 0;
        spawns++;

        Vec2 loc = Random::randVecInViewport();

        int randMax = std::min(enemies.size()-1, (size_t)spawns/4);
        int nextEnemyIndex = Random::randInt(0, randMax);

        GameObject& newEnemy = enemies[nextEnemyIndex]->create(loc);
        EnemyController* controller = newEnemy.getComponent<EnemyController>();

        controller->setTarget(player);
    }
}

void Spawner::addEnemyPrefab(Prefab* e){
    enemies.push_back(e);
}