#pragma once
#include "Component.h"
#include "Prefab.h"

#include <memory>

class Spawner : public Component{
    public:
    Spawner(GameObject& obj, GameObject& playerObj);

    void update(float dt) override;

    int getID() override;

    void setEnemyPrefab(Prefab* e);
    private:
    GameObject& player;

    Prefab* enemy;
    float spawnState = 0;
    float spawnRate = 5;
};