#pragma once
#include "Bullet.h"

class Prefab;

class ShotgunShell : public BulletParent<ShotgunShell> {
    public:
    ShotgunShell(GameObject* obj, Prefab* projectiles);

    void update(float dt) override;

    private:
    Prefab* projectile;
};