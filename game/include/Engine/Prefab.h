#pragma once
#include "GameObject.h"

#include "Renderer.h"
#include "BodyComponent.h"

#include <phys2d/maths/vec2.h>
#include <phys2d/World.h>
#include <phys2d/colliders/Shape.h>

#include <memory>

class Prefab{
    GameObject templateObject;
    Body body;
public:
    Prefab(GameObject&& t, Body b) : templateObject(t), body(b){

    }

    Prefab() : templateObject(std::make_unique<NullRenderer>()){
        
    }

    virtual GameObject& create(phys2d::Vec2 pos, float rotation=0.0f){
        GameObject prepObj = GameObject(templateObject);
        prepObj.addComponent<BodyComponent>(BodyComponent::world->createBody(&body));
        prepObj.getComponent<BodyComponent>()->body->position = pos;
        prepObj.getComponent<BodyComponent>()->body->rotation = rotation;

        GameObject& obj = GameObject::addObject(std::move(prepObj));

        return obj;
    }
};
