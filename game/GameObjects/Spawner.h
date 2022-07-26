#pragma once
#include "Component.h"
#include "Prefab.h"

#include <memory>

class Spawner : public Component{
    public:
    Gun(GameObject& obj, GameObject& playerObj);

    void update(float dt) override;

    int getID() override;
    private:
    Prefab* enemy;
    float spawnState = 0;
    float spawnRate = 5;
};