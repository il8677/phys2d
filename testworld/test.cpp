#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <phys2d/World.h>
#include <phys2d/Body.h>
#include <phys2d/colliders/Shape.h>

// Debug header
#include "../phys2d/src/colliders/Collision.h"
#include "GameObject.h"

#include <imgui.h>
#include <imgui-SFML.h>

#include <functional>
#include <unordered_map>

sf::RenderWindow window(sf::VideoMode(1920, 1200), "My window");
phys2d::World world({0,0});

sf::View mainView(sf::FloatRect(0, 0, 16, 10));

using namespace phys2d;

inline sf::Vector2f vec2conv(phys2d::Vec2 v){
    return sf::Vector2f(v.x, v.y);
}

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


class DebugRenderer{
    public:
    static void renderContacts(){
        auto contacts = world.d_getContacts();

        for(const auto& contact : contacts){
            if(!contact.inContact) continue;

        sf::Vertex line[] = {
            sf::Vertex(vec2conv(contact.contactPoint - contact.normal*0.5f)),
            sf::Vertex(vec2conv(contact.contactPoint + contact.normal*0.5f))
        };

            window.draw(line, 2, sf::Lines);
        }
    }
};

struct Scene{
    Scene(const char* name_, std::function<void()> setup_) : 
        name(name_), setup(setup_){

    }
    
    const char* name;
    std::function<void()> setup;  
};

void particleWorld(int particlen, std::vector<GameObject>& objects){
    
    int particleCount = particlen*particlen;

    const int startx = 1;
    const int endx = 15;

    const int starty = 1;
    const int endy = 9;

    float incx = (endx - startx) / (float)particlen;
    float incy = (endy - starty) / (float)particlen;

    objects.reserve(particleCount);

    for(int x = 0; x < particlen; x++){
        for(int y = 0; y < particlen; y++){
            objects.emplace_back(GameObject::createCircle(world, BodyData(0.1f), Vec2(startx + incx * x, starty + incy * y), incy/4));

            objects.back().body->velocity = Vec2(randomFloat(-1, 1), randomFloat(-1, 1));
        }
    }
}

int main(){
    // SFML setup
    window.setFramerateLimit(60);
    window.setView(mainView);

    std::vector<GameObject> objects;

    // Scenes
    std::map<std::string, std::vector<Scene>> scenes;

    { // Special tests
        scenes["glitched"].push_back(Scene("Inside", [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(2.5, 5)));
        }));

        scenes["glitched"].push_back(Scene("Connected Chain",
            [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(2.9, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(5, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(0.1f), Vec2(7, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(0.1f), Vec2(9, 5)));


            objects[0].body->velocity = Vec2(1.5f, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));
    }

    { // Circles

        scenes["circles"].push_back(Scene("Circle Collision 1",
        [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(5, 5)));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(-1, 0);
        }));

        scenes["circles"].push_back(Scene("Circle Collision 2",
            [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(5, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(0.1f), Vec2(7.1, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(0.1f), Vec2(9.2, 5)));


            objects[0].body->velocity = Vec2(1.5f, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["circles"].push_back(Scene("Size Difference 1", [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(1, 5), 1));
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(5, 6), 0.5f));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["circles"].push_back(Scene("Size Difference 2", [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createCircle(world, BodyData(0.4f), Vec2(5, 5.5f), 0.25f));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["circles"].push_back(Scene("Pool 1",
            [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(10), Vec2(1, 5)));

            for(int x = 0; x < 5; x++){
                for(int y = 0; y < 5; y++){
                    objects.push_back(GameObject::createCircle(world, BodyData(1/5.f), Vec2(6+(x-5)*0.2f, 5+(y-5)*0.2f), 0.2f));
                }
            }

            objects[0].body->velocity = Vec2(1, 0);
        }));
    }

    { // Squares

        scenes["squares"].push_back(Scene("Circle Collision 1",
        [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 5)));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(-1, 0);
        }));

        scenes["squares"].push_back(Scene("Circle Collision 2",
            [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 5)));


            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["squares"].push_back(Scene("Size Difference 1", [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(2), Vec2(1, 5), 1));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 6), 0.5f));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["squares"].push_back(Scene("Size Difference 2", [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(0.4f), Vec2(5, 5.5f), 0.25f));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["squares"].push_back(Scene("Pool 1",
            [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(10), Vec2(1, 5)));

            for(int x = 0; x < 5; x++){
                for(int y = 0; y < 5; y++){
                    objects.push_back(GameObject::createSquare(world, BodyData(1/5.f), Vec2(6+(x-5)*0.2f, 5+(y-5)*0.2f), 0.2f));
                }
            }

            objects[0].body->velocity = Vec2(1, 0);
        }));
    }

    { // Stress
        scenes["stress"].emplace_back("Particle World 10^2", [&](){
            particleWorld(10, objects);
        });

        scenes["stress"].emplace_back("Particle World 16^2", [&](){
            particleWorld(16, objects);
        });

        scenes["stress"].emplace_back("Particle World 100^2", [&](){
            particleWorld(100, objects);
        });
    }

    // IMGUI debug
    ImGui::SFML::Init(window);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    

    // Settings
    bool doPhysTick = true;
    bool doBreak = false;

    bool doContactRender = false;

    float tickDT = 1/20;
    
    scenes["circles"][1].setup();
    
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

        const float moveAmount = 10.f;

        sf::Time elapsed = clock.restart();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            mainView.move(0, -moveAmount*elapsed.asSeconds());
            window.setView(mainView);
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            mainView.move(-moveAmount*elapsed.asSeconds(), 0);
            window.setView(mainView);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            mainView.move(0, moveAmount*elapsed.asSeconds());
            window.setView(mainView);
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            mainView.move(moveAmount*elapsed.asSeconds(), 0);
            window.setView(mainView);
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // Phys update
        if(physClock.getElapsedTime().asSeconds() > 1/60.f && doPhysTick){
            world.step(1/60.f);
        }

        // Logic update
        for(GameObject& go : objects){
            go.tick(elapsed.asSeconds(), window);
        }

        ImGui::SFML::Update(window, elapsed);

        ImGui::Begin("Scenes");
        
        for (std::pair<std::string, std::vector<Scene>> kv : scenes){
            if(ImGui::CollapsingHeader(kv.first.c_str())){
                for(size_t i = 0; i < kv.second.size(); i++){
                    if(ImGui::Button(kv.second[i].name)) {
                        objects.clear();
                        world.reset();
                        kv.second[i].setup();
                    }
                }
            }
        }

        ImGui::End();

        ImGui::Begin("Peformance");
        ImGui::Text("dt %dms", elapsed.asMilliseconds());
        ImGui::Text("Ct %u", world.d_getContacts().size());
        ImGui::End();

        ImGui::Begin("Debug");

        ImGui::InputFloat2("Gravity", (float*)&world.d_getGravity());

        if(ImGui::CollapsingHeader("Control")){
            ImGui::Checkbox("Phys Tick", &doPhysTick);

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

        if(ImGui::CollapsingHeader("Rendering")){
            ImGui::Checkbox("Contact Render", &doContactRender);
        }

        if(ImGui::CollapsingHeader("Objects")){
            ImGui::Text("Object count: %d", objects.size());
            for(const GameObject& go : objects){
                ImGui::Text("m %f vx %f vy %f px %f py %f", go.body->data.getMass(), go.body->velocity.x, go.body->velocity.y, go.body->position.x, go.body->position.y);
            }
        }
        ImGui::End();
        ImGui::EndFrame();

        ImGui::SFML::Render(window);

        if(doContactRender){
            DebugRenderer::renderContacts();
        }

        // Update and Render additional Platform Windows
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        // end the current frame
        window.display();
    }

    return 0;
}
