#include "Input.h"

float Input::getMouseX(){
    return mouse.x/maxX * viewportX;
}

float Input::getMouseY(){
    return mouse.y/maxY * viewportY;
}

void Input::setKeyState(sf::Keyboard::Key code, bool state){
    pressed[code] = state;
}

bool Input::getKeyState(sf::Keyboard::Key code){
    return pressed[code];
}

bool Input::pressed[];
float Input::viewportX, Input::viewportY;
float Input::maxX, Input::maxY;
decltype(Input::mouse) Input::mouse;