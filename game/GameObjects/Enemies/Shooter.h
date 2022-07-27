#pragma once
#include "EnemyController.h"

#include <Engine/Prefab.h>

#include <memory>

class Shooter : public EnemyController{
    public:
    Shooter(GameObject* obj);
    virtual Component* clone(GameObject* newObj) override;

    void update(float dt) override;

    void setBulletPrefab(Prefab* comp);

    protected:
    virtual void shoot(float dt);
    virtual void movement(float dt);

    Prefab* bullet;

    float fireState = 0;
    float fireRate = 1;

    float timer = 0;
};