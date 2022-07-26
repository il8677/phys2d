#pragma once
#include "EnemyController.h"
#include "Prefab.h"

#include <memory>

class Suicider : public EnemyController{
    public:
    Suicider(GameObject* obj);
    Component* clone(GameObject* newObj) const override;

    void update(float dt) override;

    private:
    float speed = 1;
};