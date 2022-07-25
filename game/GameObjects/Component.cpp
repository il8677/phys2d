#include "Component.h"

Component::~Component(){
    
}

Component::Component(GameObject& gameObject_) : gameObject(gameObject_){

}

void Component::setup(){
    
}

void Component::start(){
    
}

void Component::destroy(){

}

int Component::componentCounter = 0;