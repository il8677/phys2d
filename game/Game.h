#pragma once

#include "GameObjects/GameObject.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <phys2d/World.h>

#include <memory>
#include <list>

class Game{
    public:
    Game();

    void mainloop();

    private:
    void handleEvents();
    void handlePhysics();
    void handleLogic();



    const int aspectX = 16;
    const int aspectY = 10;

    const int viewX = aspectX * 60;
    const int viewY = aspectY * 60;

    sf::RenderWindow window;
    phys2d::World world;

    sf::Clock clock;
    sf::Clock physClock;

    sf::View mainView;

    std::list<GameObject> objects;
};