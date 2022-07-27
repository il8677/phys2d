#pragma once

#include "Shooter.h"

class Elite : public Shooter{
    public:
    Elite(GameObject* obj);
    virtual Component* clone(GameObject* newObj) override;

    private:
    void movement(float dt) override;
    
    Vec2 target;
};