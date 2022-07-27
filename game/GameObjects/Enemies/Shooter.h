#pragma once
#include "EnemyController.h"

#include <Engine/Prefab.h>

#include <memory>

class Shooter : public EnemyController{
    public:
    Shooter(GameObject* obj);
    Component* clone(GameObject* newObj) const override;

    void setup() override;
    void update(float dt) override;

    void setBulletPrefab(Prefab* comp);

    private:
    Prefab* bullet;

    float fireState = 0;
    float fireRate = 1;

    float timer = 0;
};