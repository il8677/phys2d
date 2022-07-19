#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <phys2d/World.h>
#include <phys2d/Body.h>
#include <phys2d/colliders/Shape.h>

#include "phys2d/src/colliders/Collision.h"

#include <imgui.h>
#include <imgui-SFML.h>

#include <functional>

sf::RenderWindow window(sf::VideoMode(1280, 700), "My window");
phys2d::World world({0,0});

using namespace phys2d;

class GameObject{
    public:

    GameObject(float mass, Vec2 pos, float r=50.f) : circle(r){
        circle.setFillColor(sf::Color(150, 50, 250));
        body = world.createBody(
            std::unique_ptr<Shape>(new ShapeCircle(r)), BodyData(mass));
        body->position = pos;
    }

    void tick(float dt){
        window.draw(circle);
        circle.setPosition(body->position.x, body->position.y);
    }

    phys2d::Body* body;
    private:
    sf::CircleShape circle;
};

struct Scene{
    Scene(const char* name_, std::function<void()> setup_) : 
        name(name_), setup(setup_){

    }
    
    const char* name;
    std::function<void()> setup;  
};

int main(){
    window.setFramerateLimit(60);

    std::vector<GameObject> objects;

    std::vector<Scene> scenes;

    scenes.push_back(Scene("Circle Collision 1",
        [&](){
        objects.emplace_back(2, Vec2(50, 100));
        objects.emplace_back(1, Vec2(300, 100));

        objects[0].body->velocity = Vec2(100, 0);
        objects[1].body->velocity = Vec2(-100, 0);
    }));

    scenes.push_back(Scene("Circle Collision 2",
        [&](){
        objects.emplace_back(2, Vec2(50, 100));
        objects.emplace_back(1, Vec2(300, 100));

        objects[0].body->velocity = Vec2(100, 0);
        objects[1].body->velocity = Vec2(0, 0);
    }));

    scenes.push_back(Scene("Size Difference 1", [&](){
        objects.emplace_back(2, Vec2(50, 100));
        objects.emplace_back(1, Vec2(300, 100), 25);

        objects[0].body->velocity = Vec2(100, 0);
        objects[1].body->velocity = Vec2(0, 0);
    }));

    scenes.push_back(Scene("Size Difference 2", [&](){
        objects.emplace_back(2, Vec2(50, 100));
        objects.emplace_back(1, Vec2(300, 100), 10);

        objects[0].body->velocity = Vec2(100, 0);
        objects[1].body->velocity = Vec2(0, 0);
    }));

    scenes.push_back(Scene("Pool 1",
        [&](){
        objects.emplace_back(1, Vec2(150, 400), 50);

        for(int x = 0; x < 5; x++){
            for(int y = 0; y < 5; y++){
                objects.emplace_back(1/5.f, Vec2(400+(x-5)*25, 500+(y-5)*25), 10);
            }
        }

        objects[0].body->velocity = Vec2(10, 0);
    }));

    scenes.push_back(Scene("Pool 2",
        [&](){
        objects.emplace_back(1, Vec2(150, 400));

        for(int x = 0; x < 5; x++){
            for(int y = 0; y < 5; y++){
                objects.emplace_back(1/5.f, Vec2(400+(x-5)*21, 500+(y-5)*21), 10);
            }
        }

        objects[0].body->velocity = Vec2(25, 0);
    }));

    ImGui::SFML::Init(window);

    bool doPhysTick = true;
    bool doBreak = false;
    float tickDT = 1/20;

    sf::Clock clock;
    sf::Clock physClock;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // Phys update
        if(physClock.getElapsedTime().asSeconds() > 1/60 && doPhysTick){
            world.step(physClock.restart().asSeconds());
        }

        // Logic update
        for(GameObject& go : objects){
            go.tick(elapsed.asSeconds());
        }

        ImGui::SFML::Update(window, elapsed);
        ImGui::Begin("Debug");

        ImGui::InputFloat2("Gravity", (float*)&world.d_getGravity());

        if(ImGui::CollapsingHeader("Scenes")){
            for(int i = 0; i < scenes.size(); i++){
                if(ImGui::Button(scenes[i].name)) {
                    objects.clear();
                    world.reset();
                    scenes[i].setup();
                }
            }
        }

        if(ImGui::CollapsingHeader("Control")){
            if(ImGui::Checkbox("Phys Tick", &doPhysTick)){
                physClock.restart();
            }

            if(ImGui::Button("Tick") && !doPhysTick) world.step(tickDT);
            ImGui::SliderFloat("Tick DT", &tickDT, 1/20, 1);

            if(ImGui::Checkbox("Break On Coll", &doBreak)){
                if(doBreak){
                    world.collCB = [&doPhysTick](Contact& c){
                        doPhysTick = false;
                    };
                }else{
                    world.collCB = [](Contact& c){};
                }
            }

        }

        if(ImGui::CollapsingHeader("Objects")){
            for(const GameObject& go : objects){
                ImGui::Text("m %f vx %f vy %f", go.body->data.getMass(), go.body->velocity.x, go.body->velocity.y);
            }
        }
        ImGui::End();
        ImGui::EndFrame();

        ImGui::SFML::Render(window);
        // end the current frame
        window.display();
    }


    return 0;
}