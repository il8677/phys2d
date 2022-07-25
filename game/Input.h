#pragma once

#include <SFML/Window/Event.hpp>

class Game;
class Input{
    public:
    static bool getKeyState(sf::Keyboard::Key code);
    static float getMouseX();
    static float getMouseY();

    static bool getMouseL();
    static bool getMouseR();

    private:

    static void setKeyState(sf::Keyboard::Key code, bool state);
    static bool pressed[sf::Keyboard::Key::KeyCount];

    static struct{
        int x, y;
        bool buttonL, buttonR;
    }mouse;

    static float viewportX, viewportY;
    static float maxX, maxY;

    friend class Game;
};