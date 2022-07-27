#include "Bullet.h"

class Prefab;

class RocketBullet : public BulletParent<RocketBullet> {
    public:
    RocketBullet(GameObject* obj, Prefab* projectiles);

    void destroy() override;

    private:
    Prefab* projectile;
};