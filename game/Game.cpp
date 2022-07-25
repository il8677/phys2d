#include "Game.h"
#include "Input.h"

#include "GameObjects/Player.h"
#include "GameObjects/Gun.h"

#include <phys2d/maths/vec2.h>
#include <phys2d/Body.h>
#include <phys2d/colliders/Shape.h>


using namespace phys2d;
std::initializer_list<Vec2> square = {{1,1}, {1,-1}, {-1, -1},{-1,1}};

Game::Game() : 
    window(sf::VideoMode(viewX, viewY), "My window"),
    world({0,0}), mainView(sf::FloatRect(0,0, aspectX*10, aspectY*10)),
    pistolBullet(Body(new ShapePoly(), BodyData(0.1f)), std::make_unique<PolyRenderer>(square, 0xFFC914FF)) {
        
    //TODO: better solution
    Input::maxX = viewX;
    Input::maxY = viewY;
    Input::viewportX = aspectX*10;
    Input::viewportY = aspectY*10;

    BodyComponent::world = &world;

    window.setFramerateLimit(60);
    window.setView(mainView);

    GameObject& player = GameObject::addObject(GameObject::createCircle(world, 0x79B342FF, BodyData(1), Vec2(50,50), 2.f, Body::BodyType::KINEMATIC));
    player.addComponent<Player>();

    GameObject& playerGun = GameObject::addObject(GameObject::createRect(world, 0x649537FF, BodyData(1), Vec2(0,0), 0.5f, 0.75f));
    playerGun.addComponent<Gun>(player);
    playerGun.getComponent<Gun>()->setBulletPrefab(&pistolBullet);


    // Outer walls
    GameObject::addObject(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(0, aspectY*5), 1, aspectY*5, Body::BodyType::STATIC));
    GameObject::addObject(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*10, aspectY*5), 1, aspectY*5, Body::BodyType::STATIC));
    GameObject::addObject(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*5, 0), aspectX*5, 1, Body::BodyType::STATIC));
    GameObject::addObject(GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*5, aspectY*10), aspectX*5, 1, Body::BodyType::STATIC));

    // ImGui
    ImGui::SFML::Init(window);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    

}

void Game::mainloop(){
    for(GameObject& obj : GameObject::objects) obj.setup();

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
        } else if (event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Right) {
                Input::mouse.buttonR = true;
            } else if(event.mouseButton.button == sf::Mouse::Left) {
                Input::mouse.buttonL = true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if(event.mouseButton.button == sf::Mouse::Right) {
                Input::mouse.buttonR = false;
            } else if(event.mouseButton.button == sf::Mouse::Left) {
                Input::mouse.buttonL = false;
            }
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
    elapsed = clock.restart();

    for(auto it = GameObject::objects.begin(); it != GameObject::objects.end(); it++){
        GameObject& go = *it;
        if(go.doDestroy){
            for(auto& c : go.components) c->destroy();
            it = GameObject::objects.erase(it);
            continue;
        }
        go.tick(elapsed.asSeconds(), window);
    }

    ImGui::SFML::Update(window, elapsed);
}

void Game::handleImGui(){

    ImGui::Begin("Debug");
    ImGui::Text("Mouse: (%.2f, %.2f)", Input::getMouseX(), Input::getMouseY());
    ImGui::Text("Objects: %u", GameObject::objects.size());
    ImGui::Text("dt: %ums", elapsed.asMilliseconds());
    ImGui::End();

    ImGui::EndFrame();

    ImGui::SFML::Render(window);

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}