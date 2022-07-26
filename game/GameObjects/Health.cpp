#include "Health.h"

#include "GameObject.h"

Health::Health(GameObject& obj) : Component(obj){
    deathCallback = [&](){obj.destroy();};
}

void Health::setMaxHealth(float amount){
    maxHealth = amount;
    health = amount;
}

void Health::damage(float amount){
    health -= amount;
    if(health <= 0){
        deathCallback();
    }
}

void Health::heal(float amount){
    health += amount;
    if(health > maxHealth) health = maxHealth;
}

void Health::update(float dt) {

}

int Health::getID(){
    return Component::getID<Health>();
}

void Health::setDeathCB(std::function<void()> dc){
    deathCallback = dc;
}