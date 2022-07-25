#pragma once

#include "Component.h"

#include <phys2d/maths/vec2.h>

class Bullet : public Component {
    public:

    void start() override;
    virtual void update(float dt) override;
    void setTravelVector(phys2d::Vec2 travelVector);
    
    int getID() override;

    float getFireRate();
    
    protected:
    Bullet(GameObject& obj, float fireRate, float bulletSpeed);
    phys2d::Vec2 travelVector;

    float fireRate;
    float speed = 100;
};