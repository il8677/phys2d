#include "Spawner.h"

#include "Suicider.h"
#include "../Input.h"

#include "../util/Random.h"

Spawner::Spawner(GameObject* obj, GameObject* playerObj) : ComponentParent(obj), player(playerObj) {
    
}

void Spawner::update(float dt){
    spawnState += dt;
    if(spawnState > spawnRate){
        spawnState = 0;
        spawns++;

        Vec2 loc = Random::randVec(Vec2(10, 10), Vec2(Input::getViewportX()-20, Input::getViewportY()-20));

        int nextEnemyIndex = Random::randInt(0, spawns/4) % enemies.size();

        GameObject& newEnemy = enemies[nextEnemyIndex]->create(loc);
        EnemyController* controller = newEnemy.getComponent<EnemyController>();

        controller->setTarget(player);
    }
}

void Spawner::addEnemyPrefab(Prefab* e){
    enemies.push_back(e);
}