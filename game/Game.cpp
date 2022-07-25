#include "Game.h"
#include "Input.h"

#include "GameObjects/Player.h"
#include "GameObjects/Gun.h"

#include <phys2d/maths/vec2.h>


using namespace phys2d;

Game::Game() : 
    window(sf::VideoMode(viewX, viewY), "My window"),
    world({0,0}), mainView(sf::FloatRect(0,0, aspectX*10, aspectY*10)) {
        
    //TODO: better solution
    Input::maxX = viewX;
    Input::maxY = viewY;
    Input::viewportX = aspectX*10;
    Input::viewportY = aspectY*10;

    window.setFramerateLimit(60);
    window.setView(mainView);

    GameObject& player = objects.emplace_back(GameObject::createCircle(world, 0x79B342FF, BodyData(1), Vec2(50,50), 2.f, Body::BodyType::KINEMATIC));
    player.addComponent<Player>();

    GameObject& playerGun = objects.emplace_back(GameObject::createRect(world, 0x649537FF, BodyData(1), Vec2(0,0), 0.5f, 0.75f));
    playerGun.addComponent<Gun>(player);

    // Outer walls
    objects.emplace_back(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(0, aspectY*5), 0.5f, aspectY*5, Body::BodyType::STATIC));
    objects.emplace_back(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*10, aspectY*5), 0.5f, aspectY*5, Body::BodyType::STATIC));
    objects.emplace_back(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*5, 0), aspectX*5, 0.5f, Body::BodyType::STATIC));
    objects.emplace_back(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*5, aspectY*10), aspectX*5, 0.5f, Body::BodyType::STATIC));

    // ImGui
    ImGui::SFML::Init(window);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    

}

void Game::mainloop(){
    for(GameObject& obj : objects) obj.setup();

    while (window.isOpen())
    {
        handleEvents();

        handlePhysics();

        window.clear(sf::Color(0x2E282AFF));
        handleLogic();
        handleImGui();

        window.display();
    }
}

void Game::handleEvents(){
    sf::Event event;
    while (window.pollEvent(event))
    {            
        ImGui::SFML::ProcessEvent(window, event);
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed){
            Input::setKeyState(event.key.code, true);
        } else if (event.type == sf::Event::KeyReleased){
            Input::setKeyState(event.key.code, false);
        } else if (event.type == sf::Event::MouseMoved){
            Input::mouse.x = event.mouseMove.x;
            Input::mouse.y = event.mouseMove.y;
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

    for(GameObject& go : objects){
        go.tick(elapsed.asSeconds(), window);
    }

    ImGui::SFML::Update(window, elapsed);
}

void Game::handleImGui(){

    ImGui::Begin("Debug");
    ImGui::Text("Mouse (%.2f, %.2f)", Input::getMouseX(), Input::getMouseY());
    ImGui::End();

    ImGui::EndFrame();

    ImGui::SFML::Render(window);

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}