#include "Component.h"

Component::~Component(){
    
}

Component::Component(GameObject* gameObject_) : gameObject(gameObject_){

}

void Component::setup(){
    
}

void Component::start(){
    
}

void Component::destroy(){

}

void Component::setGameObject(GameObject* obj){
    gameObject = obj;
}

GameObject* Component::getGo(){
    return gameObject;
}

int Component::componentCounter = 0;