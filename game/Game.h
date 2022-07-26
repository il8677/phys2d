#pragma once

#include "GameObjects/GameObject.h"
#include "GameObjects/Prefab.h"
#include "GameObjects/PistolBullet.h"
#include "GameObjects/Suicider.h"
#include "GameObjects/Health.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <phys2d/World.h>

#include <imgui.h>
#include <imgui-SFML.h>

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
    void handleImGui();

    void gameOver();

    const int aspectX = 16;
    const int aspectY = 10;

    const int viewX = aspectX * 60;
    const int viewY = aspectY * 60;

    sf::RenderWindow window;
    phys2d::World world;

    sf::Clock clock;
    sf::Clock physClock;

    sf::View mainView;

    sf::Time elapsed;
    
    Prefab pistolBullet;
    Prefab suicider;
};