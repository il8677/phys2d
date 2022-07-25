#pragma once
#include "GameObject.h"

#include "Renderer.h"
#include "BodyComponent.h"

#include <phys2d/maths/vec2.h>
#include <phys2d/World.h>
#include <phys2d/colliders/Shape.h>

#include <memory>

class Prefab{
public:
    virtual GameObject& create(phys2d::Vec2 pos)=0;
};

template<typename... Components>
class PrefabComponents : public Prefab {
    public:
    PrefabComponents(phys2d::Body templateBody_, std::unique_ptr<Renderer> renderer_) : templateBody(templateBody_), renderer(std::move(renderer_)) {

    }

    GameObject& create(phys2d::Vec2 pos) override {
        GameObject& obj = GameObject::addObject(GameObject(std::unique_ptr<Renderer>(renderer->clone())));

        obj.addComponent<BodyComponent>(BodyComponent::world->createBody(&templateBody));
        obj.getComponent<BodyComponent>()->body->position = pos;
        obj.addComponent<Components ...>();

        return obj;
    }

    private:
    phys2d::Body templateBody;
    std::unique_ptr<Renderer> renderer;
};