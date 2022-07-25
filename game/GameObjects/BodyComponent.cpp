#include "BodyComponent.h"

#include <phys2d/World.h>

void BodyComponent::destroy(){
    body->doDestroy = true;
}

BodyComponent::BodyComponent(GameObject& obj, phys2d::Body* body_) : body(body_), Component(obj) {

}

void BodyComponent::update(float dt){

}

int BodyComponent::getID(){
    return Component::getID<BodyComponent>();
}

phys2d::World* BodyComponent::world;