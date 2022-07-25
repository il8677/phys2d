#include "BodyComponent.h"

BodyComponent::BodyComponent(GameObject& obj, phys2d::Body* body_) : body(body_), Component(obj) {

}

void BodyComponent::update(float dt){

}

int BodyComponent::getID(){
    return Component::getID<BodyComponent>();
}