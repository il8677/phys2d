#include "Spawner.h"

Spawner::Spawner(GameObject& obj, GameObject& playerObj) : Component(obj), player(playerObj) {
    
}

void Spawner::update(float dt){
    spawnState += dt;
    if(spawnState > spawnRate){
        spawnState = 0;

        enemy->create({50,50});
    }
}

void Spawner::setEnemyPrefab(Prefab* e){
    enemy = e;
}

int Spawner::getID() {
    return Component::getID<Spawner>();
}