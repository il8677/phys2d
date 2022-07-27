#pragma once
#include "Bullet.h"

class PistolBullet : public BulletParent<PistolBullet> {
    public:
    PistolBullet(GameObject* obj);
    
};