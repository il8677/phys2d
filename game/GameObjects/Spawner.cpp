#include "Spawner.h"

Spawner::update(float dt){
    spawnState += dt;
    if(spawnState > spawnRate){
        spawnState = 0;

        enemy->create({50,50});
    }
}

void Spawner::getID() override{
    return Component::getID<Spawner>();
}