#pragma once
#include "Component.h"

#include <functional>

class Health : public Component{
    public:
    Health(GameObject& obj);

    void setMaxHealth(float amount);
    void damage(float amount);
    void heal(float amount);

    void update(float dt) override;
    int getID() override;

    void setDeathCB(std::function<void()> dc);

    private:
    float health=10;
    float maxHealth = 10;

    std::function<void()> deathCallback;
};