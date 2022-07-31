#include "Input.h"
#include "Game.h"

#include "GameObjects/Player/Player.h"
#include "GameObjects/Player/Gun.h"
#include "GameObjects/Helper/Spawner.h"
#include "GameObjects/Helper/Lifetime.h"
#include "GameObjects/Helper/Loot.h"
#include "GameObjects/Helper/LootDropper.h"
#include "GameObjects/Enemies/Shooter.h"
#include "GameObjects/Enemies/Elite.h"
#include "GameObjects/Bullets/PistolBullet.h"
#include "GameObjects/Bullets/SMGBullet.h"
#include "GameObjects/Bullets/RocketBullet.h"
#include "GameObjects/Bullets/ShotgunShell.h"
#include "GameObjects/Enemies/Shooter.h"

#include <Engine/Renderer.h>

#include <phys2d/maths/vec2.h>
#include <phys2d/Body.h>
#include <phys2d/colliders/Shape.h>

#define ELITESIZE 3.5f
#define ELITEA (ELITESIZE * 0.5f)
#define ELITEB (ELITESIZE * 0.866025f) 

using namespace phys2d;
std::initializer_list<Vec2> bulletModel = {{-1,0}, {0,1}, {1,0}};
std::initializer_list<Vec2> smgBulletModel = {{-0.75, 0}, {0,1.75f}, {0.75, 0}};
std::initializer_list<Vec2> suiciderModel = {{-3,-3}, {3,-3}, {3, 3},{-3,3}};
std::initializer_list<Vec2> shooterModel = {{0,3}, {-3,0}, {-2, -3}, {2, -3}, {3,0}};
std::initializer_list<Vec2> eliteModel = {{-ELITEA, -ELITEB}, {ELITEA, -ELITEB}, {ELITESIZE, 0},  {ELITEA, ELITEB},  {-ELITEA, ELITEB}, {-ELITESIZE, 0} };
std::initializer_list<Vec2> lootBoxModel = {{-1,-1}, {1,-1}, {1,1}, {-1,1}};
std::initializer_list<Vec2> shotgunPelletModel = {{-0.75f,-1}, {1,-0.75f}, {1,1}, {-0.75f,1}};
std::initializer_list<Vec2> shotgunShellModel = {{-2,0}, {-2.5f, 2}, {-1.8f, 1.f}, {-0.8f, 2.4f}, {0.2f, 1.9f}, {2,0}};

Game::Game() : 
    window(sf::VideoMode(viewX, viewY), "My window"),
    world({0,0}), mainView(sf::FloatRect(0,0, aspectX*10, aspectY*10)) {
        
    //TODO: better solution
    Input::maxX = viewX;
    Input::maxY = viewY;
    Input::viewportX = aspectX*10;
    Input::viewportY = aspectY*10;

    BodyComponent::world = &world;
    
    // Setup prefabs
    {
        GameObject suiciderObj(std::make_unique<PolyRenderer>(suiciderModel, 0xE4572EFF));
        suiciderObj.addComponent<Suicider>();
        suiciderObj.addComponent<Health>();
        suiciderObj.addComponent<LootDropper>(&rocketLoot, 0.1f);

        suicider = Prefab(std::move(suiciderObj), Body(new ShapePoly(suiciderModel), BodyData(1), Body::BodyType::KINEMATIC));

        GameObject shooterObj(std::make_unique<PolyRenderer>(shooterModel, 0x62929EFF));
        shooterObj.addComponent<Shooter>()->setBulletPrefab(&pistolBullet);
        shooterObj.addComponent<Health>(5);
        shooterObj.addComponent<LootDropper>(&pistolLoot, 0.1f);
        shooter = Prefab(std::move(shooterObj), Body(new ShapePoly(shooterModel), BodyData(1), Body::BodyType::KINEMATIC));

        GameObject eliteObj(std::make_unique<PolyRenderer>(eliteModel, 0x365259FF));
        eliteObj.addComponent<Elite>()->setBulletPrefab(&smgBullet);
        eliteObj.addComponent<Health>(9);
        eliteObj.addComponent<LootDropper>(&smgLoot, 0.15f);
        eliteObj.addComponent<LootDropper>(&shotgunLoot, 0.15f);
        elite = Prefab(std::move(eliteObj), Body(new ShapePoly(eliteModel), BodyData(0.5f), Body::BodyType::KINEMATIC));

        GameObject bulletObj(std::make_unique<PolyRenderer>(bulletModel, 0xFFC914FF));
        bulletObj.addComponent<PistolBullet>();
        pistolBullet = Prefab(std::move(bulletObj), Body(new ShapePoly(bulletModel), BodyData(0.1)));
        
        GameObject smgBulletObj(std::make_unique<PolyRenderer>(smgBulletModel, 0xFFC914FF));
        smgBulletObj.addComponent<SMGBullet>();
        smgBullet = Prefab(std::move(smgBulletObj), Body(new ShapePoly(smgBulletModel), BodyData(0.1f)));

        GameObject rocketObj(std::make_unique<CircleRenderer>(1.25f, 0xFFC914FF));
        rocketObj.addComponent<RocketBullet>(&pistolBullet);
        rocketBullet = Prefab(std::move(rocketObj), Body(new ShapeCircle(1.25f), BodyData(1)));

        GameObject shotgunPelletObj(std::make_unique<PolyRenderer>(shotgunPelletModel, 0xFFC914AA));
        shotgunPelletObj.addComponent<PistolBullet>(4);
        shotgunPelletObj.addComponent<Lifetime>(0.75f);
        shotgunPellet = Prefab(std::move(shotgunPelletObj), Body(new ShapePoly(shotgunPelletModel), BodyData(0.1f)));

        GameObject shotgunShellObj(std::make_unique<PolyRenderer>(shotgunShellModel, 0xFFC914AA));
        shotgunShellObj.addComponent<ShotgunShell>(&shotgunPellet);
        shotgunShell = Prefab(std::move(shotgunShellObj), Body(new ShapeCircle(0), BodyData(0.1f)));


        GameObject pistolLootObj(std::make_unique<PolyRenderer>(lootBoxModel, 0x88423AFF));
        pistolLootObj.addComponent<Loot>(&pistolBullet);
        pistolLoot = Prefab(std::move(pistolLootObj), Body(new ShapePoly(lootBoxModel), BodyData(1)));

        GameObject smgLootObj(std::make_unique<PolyRenderer>(lootBoxModel, 0xB82FACFF));
        smgLootObj.addComponent<Loot>(&smgBullet);
        smgLoot = Prefab(std::move(smgLootObj), Body(new ShapePoly(lootBoxModel), BodyData(1)));

        GameObject rocketLootObj(std::make_unique<PolyRenderer>(lootBoxModel, 0x7823FFF));
        rocketLootObj.addComponent<Loot>(&rocketBullet);
        rocketLoot = Prefab(std::move(rocketLootObj), Body(new ShapePoly(lootBoxModel), BodyData(1)));

        GameObject shotgunLootObj(std::make_unique<PolyRenderer>(lootBoxModel, 0x9FC293FF));
        shotgunLootObj.addComponent<Loot>(&shotgunShell);
        shotgunLoot = Prefab(std::move(shotgunLootObj), Body(new ShapePoly(lootBoxModel), BodyData(1)));
    }

    window.setFramerateLimit(60);
    window.setView(mainView);

    setupGame();

    // ImGui
    /*
    ImGui::SFML::Init(window);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    
    */
}

void Game::setupGame(){
    restartGame = false;
    GameObject::objects.clear();
    world.clear();

    GameObject& player = GameObject::createCircle(world, 0x79B342FF, BodyData(1), Vec2(50,50), 2.f, Body::BodyType::KINEMATIC);
    player.addComponent<Health>();
    player.getComponent<Health>()->setDeathCB([&](){gameOver();});

    GameObject& playerGun = GameObject::createRect(world, 0x649537FF, BodyData(1), Vec2(0,0), 0.5f, 0.75f);
    Gun* playerGunComp = playerGun.addComponent<Gun>(player);
    playerGun.getComponent<Gun>()->setBulletPrefab(&pistolBullet);
    playerGun.getComponent<BodyComponent>()->body->layer = 0;

    player.addComponent<Player>(playerGunComp);

    GameObject& spawner = GameObject::addObject(GameObject(std::make_unique<NullRenderer>()));
    Spawner* s = spawner.addComponent<Spawner>(&player);
    s->addEnemyPrefab(&suicider);
    s->addEnemyPrefab(&shooter);
    s->addEnemyPrefab(&elite);

    // Outer walls
    GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(0, aspectY*5), 1, aspectY*5, Body::BodyType::STATIC);
    GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*10, aspectY*5), 1, aspectY*5, Body::BodyType::STATIC);
    GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*5, 0), aspectX*5, 1, Body::BodyType::STATIC);
    GameObject::createRect(world, 0x046865FF, BodyData(0,0), Vec2(aspectX*5, aspectY*10), aspectX*5, 1, Body::BodyType::STATIC);
}

void Game::mainloop(){
    while (window.isOpen())
    {
        if(restartGame) setupGame();

        handleEvents();

        handlePhysics();

        window.clear(sf::Color(0x2E282AFF));
        handleLogic();
        //handleImGui();

        window.display();
    }
}

void Game::handleEvents(){
    sf::Event event;
    while (window.pollEvent(event))
    {            
        //ImGui::SFML::ProcessEvent(window, event);
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
            it->onDestroy();
            it = GameObject::objects.erase(it);
            continue;
        }
        go.tick(elapsed.asSeconds(), window);
    }

    //ImGui::SFML::Update(window, elapsed);
}

void Game::handleImGui(){

    ImGui::Begin("Debug");
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

void Game::gameOver(){
    restartGame = true;
}