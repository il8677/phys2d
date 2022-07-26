#include "Health.h"

#include "GameObject.h"

Health::Health(GameObject* obj) : ComponentParent(obj){
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

    uint32_t currentColor = gameObject->getRenderer()->getColor();
    gameObject->getRenderer()->setColor(currentColor & 0xFFFFFF00 | (int)(0xFF*health/(float)maxHealth));
}

void Health::heal(float amount){
    health += amount;
    if(health > maxHealth) health = maxHealth;

    uint32_t currentColor = gameObject->getRenderer()->getColor();
    gameObject->getRenderer()->setColor(currentColor & 0xFFFFFF00 | (int)(0xFF*health/(float)maxHealth));
}

void Health::update(float dt) {

}

void Health::setDeathCB(std::function<void()> dc){
    deathCallback = dc;
}