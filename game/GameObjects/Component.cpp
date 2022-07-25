#include "Component.h"

Component::Component(GameObject& gameObject_) : gameObject(gameObject_){

}

int Component::componentCounter = 0;