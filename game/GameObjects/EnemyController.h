#pragma once
#include "Component.h"
#include "Prefab.h"

#include <memory>

class EnemyController : public Component{
    public:
    EnemyController(GameObject* obj);
    virtual Component* clone(GameObject* newObj) const override=0;    
    int getID() override;

    void update(float dt) override=0;

    void setTarget(GameObject* target);

    protected:
    GameObject* target = nullptr;
};