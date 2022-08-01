#include "Input.h"

float Input::getMouseX(){
    return mouse.x/maxX * viewportX;
}

float Input::getMouseY(){
    return mouse.y/maxY * viewportY;
}

bool Input::getMouseL(){
    return mouse.buttonL;
}

bool Input::getMouseR(){
    return mouse.buttonR;
}

void Input::setKeyState(sf::Keyboard::Key code, bool state){
    pressed[code] = state;
}

bool Input::getKeyState(sf::Keyboard::Key code){
    return pressed[code];
}

float Input::getViewportX(){
    return viewportX;
}
float Input::getViewportY(){
    return viewportY;
}

bool Input::pressed[];
float Input::viewportX, Input::viewportY;
float Input::maxX, Input::maxY;
decltype(Input::mouse) Input::mouse;