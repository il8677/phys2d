#include <Engine/BodyComponent.h>

#include <phys2d/World.h>

Component* BodyComponent::clone(GameObject* newObj) {
    BodyComponent* n = (BodyComponent*)ComponentParent<BodyComponent>::clone(newObj);
    
    // Create a new body for the new component
    n->body = world->createBody(body);
    
    n->setGameObject(newObj);

    return n;
}

void BodyComponent::setGameObject(GameObject* obj){
    Component::setGameObject(obj);
    body->userData = (void*)obj;
}

void BodyComponent::destroy(){
    body->doDestroy = true;
}

BodyComponent::BodyComponent(GameObject* obj, phys2d::Body* body_) : body(body_), ComponentParent(obj) {
    body->userData = (void*)obj;
}

void BodyComponent::update(float dt){
    if(body->userData != gameObject){
        body->userData = gameObject;
    }
}

phys2d::World* BodyComponent::world;