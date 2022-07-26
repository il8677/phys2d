#pragma once
#include "Component.h"
#include "Prefab.h"

#include <memory>

class Gun : public ComponentParent<Gun>{
    public:
    Gun(GameObject* obj, GameObject& playerObj);

    void setup() override;
    void update(float dt) override;

    void setBulletPrefab(Prefab* comp);

    private:
    Prefab* bullet;
    GameObject& player;

    float fireState = 0;
    float fireRate = 1;
};