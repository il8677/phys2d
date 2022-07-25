#include "Game.h"
#include "Input.h"

#include "GameObjects/Player.h"

#include <phys2d/maths/vec2.h>

using namespace phys2d;

Game::Game() : 
    window(sf::VideoMode(viewX, viewY), "My window"),
    world({0,0}), mainView(sf::FloatRect(0,0, aspectX*10, aspectY*10)) {
        
    window.setFramerateLimit(60);
    window.setView(mainView);

    objects.emplace_back(std::make_unique<Player>(world, phys2d::Vec2(50,50)));

    // Outer walls
    objects.emplace_back(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(0, aspectY*5), 0.5f, aspectY*5, Body::BodyType::STATIC));
    objects.emplace_back(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*10, aspectY*5), 0.5f, aspectY*5, Body::BodyType::STATIC));
    objects.emplace_back(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*5, 0), aspectX*5, 0.5f, Body::BodyType::STATIC));
    objects.emplace_back(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*5, aspectY*10), aspectX*5, 0.5f, Body::BodyType::STATIC));
}

void Game::mainloop(){
    while (window.isOpen())
    {
        handleEvents();

        handlePhysics();

        window.clear(sf::Color(0x2E282AFF));
        handleLogic();

        window.display();
    }
}

void Game::handleEvents(){
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed){
            Input::setKeyState(event.key.code, true);
        } else if (event.type == sf::Event::KeyReleased){
            Input::setKeyState(event.key.code, false);
        }
    }
}

void Game::handlePhysics(){
    if(physClock.getElapsedTime().asSeconds() > 1/60.f){
        world.step(1/60.f);
        physClock.restart();
    }
}

void Game::handleLogic(){
    sf::Time elapsed = clock.restart();

    for(std::unique_ptr<GameObject>& go : objects){
        go->tick(elapsed.asSeconds(), window);
    }
}