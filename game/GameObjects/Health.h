#pragma once
#include "Component.h"

class Health : public Component{
    public:
    Health(GameObject& obj);

    void setHealth(float amount);
    void damage(float amount);

    private:
    float health=10;
};