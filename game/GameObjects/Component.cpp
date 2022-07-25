#include "Component.h"

Component::Component(GameObject& gameObject_) : gameObject(gameObject_){

}

void Component::setup(){
    
}

int Component::componentCounter = 0;