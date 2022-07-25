#pragma once

#include <SFML/Window/Event.hpp>

class Game;
class Input{
    public:
    static bool getKeyState(sf::Keyboard::Key code);

    private:

    static void setKeyState(sf::Keyboard::Key code, bool state);
    static bool pressed[sf::Keyboard::Key::KeyCount];

    friend class Game;
};