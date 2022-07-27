#pragma once
#include "Bullet.h"

class SMGBullet : public BulletParent<SMGBullet>{
    public:
    SMGBullet(GameObject* obj, int count=0);
    void onClone(Component* clone) override;

    float getFireRate() override;

    private:
    int count;
};