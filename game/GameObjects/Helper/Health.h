#pragma once
#include <Engine/Component.h>

#include <functional>

class Health : public ComponentParent<Health>{
    public:
    Health(GameObject* obj, float maxHealth=10);

    void setMaxHealth(float amount);
    void damage(float amount);
    void heal(float amount);

    void update(float dt) override;

    void setDeathCB(std::function<void()> dc);

    private:
    float health=10;
    float maxHealth = 10;

    std::function<void()> deathCallback;
};