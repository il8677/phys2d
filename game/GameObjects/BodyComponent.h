#pragma once
#include "Component.h"

#include <phys2d/Body.h>
#include <phys2d/World.h>

class BodyComponent : public Component{
    public:
    BodyComponent(GameObject& obj, phys2d::Body* body);

    void update(float dt) override;
    int getID() override;

    phys2d::Body* body;

    static phys2d::World* world;
};