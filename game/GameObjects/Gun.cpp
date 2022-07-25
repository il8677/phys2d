#include "Gun.h"

#include "../Input.h"
#include "GameObject.h"
#include "BodyComponent.h"

#include <phys2d/Body.h>
#include <phys2d/maths/vec2.h>

Gun::Gun(GameObject& obj, GameObject& playerObj) :
    Component(obj), player(playerObj){

}

void Gun::setup() {
    phys2d::Body* body = gameObject.getComponent<BodyComponent>()->body;
    body->layer = 0;
}

void Gun::update(float dt) {
    phys2d::Body* body = gameObject.getComponent<BodyComponent>()->body;
    phys2d::Body* playerBody = player.getComponent<BodyComponent>()->body;

    const phys2d::Vec2 mousePos(Input::getMouseX(), Input::getMouseY());
    const phys2d::Vec2 mouseVec = (playerBody->position - mousePos).normalized();

    body->position = playerBody->position - mouseVec * 3;
    body->rotation = mouseVec.getAngle()+3.1415/2;
}

int Gun::getID(){
    return Component::getID<Gun>();
}