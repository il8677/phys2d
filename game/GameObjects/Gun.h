#pragma once
#include "Component.h"

class Gun : public Component{
    public:
    Gun(GameObject& obj, GameObject& playerObj);

    void setup() override;
    void update(float dt) override;
    int getID() override;
    private:

    GameObject& player;
};