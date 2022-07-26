#pragma once
#include "Component.h"

#include <phys2d/Body.h>
#include <phys2d/World.h>

class BodyComponent : public ComponentParent<BodyComponent>{
    public:
    BodyComponent(GameObject* obj, phys2d::Body* body);

    void setGameObject(GameObject* obj) override;

    void update(float dt) override;
    void destroy() override;

    Component* clone(GameObject* newObj) const override;

    phys2d::Body* body;

    static phys2d::World* world;
};