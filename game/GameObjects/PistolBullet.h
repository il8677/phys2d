#pragma once
#include "Bullet.h"

class PistolBullet : public Bullet {
    public:
    PistolBullet(GameObject& obj);

    void setup() override;
    void update(float dt) override;

    private:
    const float speed = 100;
};