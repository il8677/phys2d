#pragma once
#include <Engine/Component.h>
#include <Engine/Prefab.h>

#include <memory>
#include <vector>

class Spawner : public ComponentParent<Spawner>{
    public:
    Spawner(GameObject* obj, GameObject* playerObj);

    void update(float dt) override;

    void addEnemyPrefab(Prefab* e);
    private:
    GameObject* player;

    std::vector<Prefab*> enemies;

    int spawns=0;

    float spawnState = 0;
    float spawnRate = 5;
};