#include "Input.h"

void Input::setKeyState(sf::Keyboard::Key code, bool state){
    pressed[code] = state;
}

bool Input::getKeyState(sf::Keyboard::Key code){
    return pressed[code];
}

bool Input::pressed[];