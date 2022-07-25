#pragma once
#include "Component.h"

#include <phys2d/Body.h>

class BodyComponent : public Component{
    public:
    BodyComponent(GameObject& obj, phys2d::Body* body);

    void update(float dt) override;
    int getID() override;

    phys2d::Body* body;
};