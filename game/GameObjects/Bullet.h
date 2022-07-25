#pragma once

#include "Component.h"

#include <phys2d/maths/vec2.h>

class Bullet : public Component {
    public:
    virtual void update(float dt) override=0;
    void setTravelVector(phys2d::Vec2 travelVector);
    
    int getID() override;

    protected:
    Bullet(GameObject& obj);
    phys2d::Vec2 travelVector;
};