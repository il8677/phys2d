#pragma once

#include <Engine/Component.h>

#include <phys2d/maths/vec2.h>

class Bullet : public Component {
    public:
    virtual Component* clone(GameObject* newObj) override=0;
    int getID() override;

    void start() override;
    virtual void update(float dt) override;
    
    void setTravelVector(phys2d::Vec2 travelVector);
    
    virtual float getFireRate();
    protected:
    Bullet(GameObject* obj, float fireRate, float bulletSpeed, float damage);
    phys2d::Vec2 travelVector;

    float fireRate;
    float speed = 100;

    float damage;
};

template <class Derived>
class BulletParent : public Bullet{
    public:
    Component* clone(GameObject* newObj) override{
        Component* c = new Derived(*((Derived*)this));
        c->setGameObject(newObj);
        onClone(c);
        return c;
    }

    protected:
    BulletParent(GameObject* obj, float fireRate, float bulletSpeed, float damage) : Bullet(obj, fireRate, bulletSpeed, damage){

    }
};