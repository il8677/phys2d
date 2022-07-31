#include "Health.h"

#include <Engine/GameObject.h>

Health::Health(GameObject* obj, float maxHealth) : ComponentParent(obj){
    setMaxHealth(maxHealth);
}

void Health::setMaxHealth(float amount){
    maxHealth = amount;
    health = amount;
}

void Health::damage(float amount){
    health -= amount;
    if(health <= 0){
        if(deathCallback) deathCallback();
        else gameObject->destroy();
    }

    updateIndicator();
}

void Health::heal(float amount){
    health += amount;
    if(health > maxHealth) health = maxHealth;

    updateIndicator();
}

void Health::update(float dt) {

}

void Health::updateIndicator(){
    uint32_t currentColor = gameObject->getRenderer()->getColor();
    gameObject->getRenderer()->setColor(currentColor & 0xFFFFFF00 | (0x55 + (int)(0xAA*health/(float)maxHealth)));
}

void Health::setDeathCB(std::function<void()> dc){
    deathCallback = dc;
}