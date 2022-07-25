#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <phys2d/World.h>
#include <phys2d/Body.h>
#include <phys2d/colliders/Shape.h>

// Debug header
#include "../src/colliders/Collision.h"
#include "GameObject.h"

#include <imgui.h>
#include <imgui-SFML.h>

#include <functional>
#include <unordered_map>

#define VX 16
#define VY 10

sf::RenderWindow window(sf::VideoMode(VX*60, VY*60), "My window");
phys2d::World world({0,0});

sf::View mainView(sf::FloatRect(0, 0, VX, VY));

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
            for(int i = 0; i < contact.contactCount; i++){
                auto contactPoint = contact.contactPoints[i];
                sf::Vertex line[] = {
                    sf::Vertex(vec2conv(contactPoint - contact.normal*0.5f), sf::Color(255,0,255)),
                    sf::Vertex(vec2conv(contactPoint + contact.normal*0.5f), sf::Color(255,0,255))
                };

                window.draw(line, 2, sf::Lines);
            }
        }
    }

    static void renderVelocities(){
        for(const Body& body : world.d_getBodies()){
            sf::Vertex line[] = {
                sf::Vertex(vec2conv(body.position), sf::Color(255,255,0)),
                sf::Vertex(vec2conv(body.position+body.velocity), sf::Color(255,255,0))
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
    world.setGravity({0, 0});
    
    int particleCount = particlen*particlen;

    const int startx = 1;
    const int endx = 15;

    const int starty = 1;
    const int endy = 9;

    float incx = (endx - startx) / (float)particlen;
    float incy = (endy - starty) / (float)particlen;

    objects.reserve(particleCount + 4);
    objects.push_back(GameObject::createRect(world, BodyData(0,1), Vec2(0, VY/2.f), 0.1f, VY/2, Body::BodyType::STATIC));
    objects.push_back(GameObject::createRect(world, BodyData(0,1), Vec2(VX, VY/2.f), 0.1f, VY/2, Body::BodyType::STATIC));
    objects.push_back(GameObject::createRect(world, BodyData(0,1), Vec2(VX/2.f, 0), VX/2, 0.1f, Body::BodyType::STATIC));
    objects.push_back(GameObject::createRect(world, BodyData(0,1), Vec2(VX/2.f, VY), VX/2, 0.1f, Body::BodyType::STATIC));

    for(int x = 0; x < particlen; x++){
        for(int y = 0; y < particlen; y++){
            objects.emplace_back(GameObject::createCircle(world, BodyData(0.1f, 1), Vec2(startx + incx * x, starty + incy * y), incy/4));
            //objects.back().body->setContinuous(true);

            objects.back().body->velocity = Vec2(randomFloat(-1, 1), randomFloat(-1, 1));
        }
    }
}

constexpr float degToRad(float angle){
    return angle * 3.1415 / 180;
}

int main(){
    // SFML setup
    window.setFramerateLimit(60);
    window.setView(mainView);

    std::vector<GameObject> objects;

    // Scenes
    std::map<std::string, std::vector<Scene>> scenes;

    { // Polygons

        scenes["polygons"].push_back(Scene("polygons Collision 1",
        [&](){
            std::initializer_list<Vec2> triangle = {
                Vec2(0,1), Vec2(-1,-1), Vec2(1,-1)
            };
            std::initializer_list<Vec2> pentagon = {
                Vec2(0,1), Vec2(-1,0), Vec2(-0.6f, -1), Vec2(0.6f, -1), Vec2(1,0)
            };
            objects.push_back(GameObject::createPoly(world, BodyData(1), Vec2(1, 5), triangle));
            objects.push_back(GameObject::createPoly(world, BodyData(1), Vec2(5, 5), pentagon));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(-1, 0);
        }));

        scenes["polygons"].push_back(Scene("polygons Collision 2",
            [&](){
            std::initializer_list<Vec2> triangle = {
                Vec2(0,1), Vec2(-1,-1), Vec2(1,-1)
            };
            std::initializer_list<Vec2> pentagon = {
                Vec2(0,1), Vec2(-1,0), Vec2(-0.6f, -1), Vec2(0.6f, -1), Vec2(1,0)
            };
            objects.push_back(GameObject::createPoly(world, BodyData(2), Vec2(1, 5), triangle));
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(5, 5)));
            objects.push_back(GameObject::createPoly(world, BodyData(0.1f), Vec2(7.1, 5), pentagon));
            objects.push_back(GameObject::createPoly(world, BodyData(0.1f), Vec2(11, 5),triangle));
            objects.push_back(GameObject::createCircle(world, BodyData(0.1f), Vec2(9.2, 5)));


            objects[0].body->velocity = Vec2(1.5f, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));
    }

    {
        scenes["specific"].push_back(Scene("polygons Friction", [&](){
            world.setGravity({0,3});
            objects.push_back(GameObject::createRect(world, BodyData(0, 1), Vec2(5,3), 3, 0.1f, Body::BodyType::STATIC));
            objects[0].body->rotation = degToRad(20);

            objects.push_back(GameObject::createRect(world, BodyData(0, 1), Vec2(9,7), 12, 0.1f, Body::BodyType::STATIC));
            objects[1].body->rotation = degToRad(360-20);

            objects.push_back(GameObject::createSquare(world, BodyData(5), Vec2(5,1), 0.75f));
            objects.push_back(GameObject::createSquare(world, BodyData(5), Vec2(5,-30), 0.75f));
            objects.push_back(GameObject::createSquare(world, BodyData(5), Vec2(5,-60), 0.75f));
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(5,-90), 0.3f));
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(5,-120), 0.5f));
        }));

        scenes["specific"].push_back(Scene("polygons Static Bounce", [&](){
            objects.push_back(GameObject::createRect(world, BodyData(0, 1), Vec2(9.5f,5), 0.2f, 4, Body::BodyType::STATIC));
            objects.push_back(GameObject::createRect(world, BodyData(0, 1), Vec2(1,5), 0.1f, 4, Body::BodyType::STATIC));

            objects.push_back(GameObject::createCircle(world, BodyData(1,1), Vec2(7,1.5f), 0.35f));

            objects[2].body->velocity = Vec2(3,0);
        }));
        scenes["specific"].push_back(Scene("bullet (non cont)", [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(1,5), 0.1f));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(1,4), 0.1f));
            objects.push_back(GameObject::createRect(world, BodyData(1), Vec2(5,5), 0.05f, 2, Body::BodyType::STATIC));

            objects[0].body->velocity = Vec2(1.15*60, 0);
            objects[1].body->velocity = Vec2(1.15*60, 0);
        }));

        scenes["specific"].push_back(Scene("bullet", [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(1,5), 0.1f));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(1,4), 0.1f));
            objects.push_back(GameObject::createRect(world, BodyData(1), Vec2(5,5), 0.05f, 2, Body::BodyType::STATIC));

            objects[0].body->velocity = Vec2(1.15*60, 0);
            objects[0].body->setContinuous(true);
            objects[1].body->velocity = Vec2(1.15*60, 0);
            objects[1].body->setContinuous(true);
        }));

        scenes["specific"].push_back(Scene("layers", [&](){
            for(int i = 0; i < 8; i++){
                // setup projectile
                objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(1,i+1), 0.1f));
                objects.back().body->velocity = {1,0};
                objects.back().body->layer = 1 << i;

                // setup walls
                objects.push_back(GameObject::createRect(world, BodyData(1), Vec2(i+2, 5), 0.1f, 4, Body::BodyType::STATIC));
                objects.back().body->layer = 1 << i;
            }

        }));
    }

    { // Circles

        scenes["circles"].push_back(Scene("Circle Collision 1",
        [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(1, 5)));
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
            objects.push_back(GameObject::createCircle(world, BodyData(0.4f), Vec2(5.3, 5.8), 0.25f));
            objects.push_back(GameObject::createCircle(world, BodyData(0.4f), Vec2(5.6, 6.1), 0.25f));
            objects.push_back(GameObject::createCircle(world, BodyData(0.4f), Vec2(5.9, 6.4), 0.25f));

            objects[0].body->velocity = Vec2(1, 0);
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

        scenes["circles"].push_back(Scene("Diagonal",
            [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(10), Vec2(1, 1)));
            objects.push_back(GameObject::createCircle(world, BodyData(5), Vec2(4, 4)));

            objects[0].body->velocity = Vec2(1, 1);
            objects[1].body->velocity = Vec2(-1, -1);
        }));
    }

    { // Squares
        scenes["squares"].push_back(Scene("Square In",
        [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(3, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(4, 5)));
            objects[0].body->velocity = {1,0};
        }));

        scenes["squares"].push_back(Scene("Square Collision 1",
        [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 5)));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(-1, 0);
        }));

        scenes["squares"].push_back(Scene("Square Collision 2",
            [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 5)));


            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["squares"].push_back(Scene("Square Size Difference 1", [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(2), Vec2(1, 5), 1));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 6), 0.5f));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["squares"].push_back(Scene("Square Size Difference 2", [&](){
            objects.push_back(GameObject::createSquare(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(4), Vec2(5, 5.5f), 0.25f));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(-1, 0);
        }));

        scenes["squares"].push_back(Scene("Square Pool 1",
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

    { // Circle Poly
        scenes["circ poly"].push_back(Scene("c-p In",
        [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(3, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(4, 5)));
        }));

        scenes["circ poly"].push_back(Scene("c-p Collision 1",
        [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(1), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 5)));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(-1, 0);
        }));

        scenes["circ poly"].push_back(Scene("c-p Collision 2",
            [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 5)));


            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["circ poly"].push_back(Scene("c-p Size Difference 1", [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(1, 5), 1));
            objects.push_back(GameObject::createSquare(world, BodyData(1), Vec2(5, 6), 0.5f));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(0, 0);
        }));

        scenes["circ poly"].push_back(Scene("c-p Size Difference 2", [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(2), Vec2(1, 5)));
            objects.push_back(GameObject::createSquare(world, BodyData(4), Vec2(5, 5.5f), 0.25f));

            objects[0].body->velocity = Vec2(1, 0);
            objects[1].body->velocity = Vec2(-1, 0);
        }));

        scenes["circ poly"].push_back(Scene("c-p Pool 1",
            [&](){
            objects.push_back(GameObject::createCircle(world, BodyData(10), Vec2(1, 5)));

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

        scenes["stress"].emplace_back("Particle World 30^2", [&](){
            particleWorld(30, objects);
        });

        scenes["stress"].emplace_back("Particle World 120^2", [&](){
            particleWorld(120, objects);
        });

        scenes["stress"].emplace_back("Particle World 200^2", [&](){
            particleWorld(200, objects);
        });
    }

    // IMGUI debug
    ImGui::SFML::Init(window);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    

    // Settings
    bool doPhysTick = true;
    bool doBreak = false;
    bool fpsLimit = true;

    bool doContactRender = false;
    bool doVelRender = false;

    bool doRender = true;

    float tickDT = 1.f/60.f;
    
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

        float moveAmount = 10.f;

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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            moveAmount+=1;
            mainView.zoom(1.1);
            window.setView(mainView);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            moveAmount-=1;
            mainView.zoom(0.9);
            window.setView(mainView);
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // Phys update
        if(physClock.getElapsedTime().asSeconds() > 1/60.f && doPhysTick){
            world.step(1/60.f);
            physClock.restart();
        }

        // Logic update
        if(doRender){
            for(GameObject& go : objects){
                go.tick(elapsed.asSeconds(), window);
            }
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
        if(ImGui::Checkbox("Framerate limit", &fpsLimit)){
            if(fpsLimit)
                window.setFramerateLimit(60);
            else
                window.setFramerateLimit(0);
            
        }
        ImGui::Checkbox("Rendering", &doRender);
        ImGui::Text("dt %dms", elapsed.asMilliseconds());
        ImGui::Text("Ct %u", world.d_getContacts().size());
        ImGui::End();

        ImGui::Begin("Debug");

        ImGui::InputFloat2("Gravity", (float*)&world.d_getGravity());

        if(ImGui::CollapsingHeader("Control")){
            ImGui::Checkbox("Phys Tick", &doPhysTick);

            if(ImGui::Button("Tick") && !doPhysTick) world.step(tickDT);
            ImGui::SliderFloat("Tick DT", &tickDT, 1/60.f, 1);

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
            ImGui::Checkbox("Velocity Render", &doVelRender);
        }

        ImGui::Text("Object count: %lu", objects.size());
        if(ImGui::CollapsingHeader("Objects")){
            for(const GameObject& go : objects){
                ImGui::Text("m %f vx %f vy %f\n av %f px %f py %f", go.body->data.getMass(), go.body->velocity.x, go.body->velocity.y, go.body->angularVel, go.body->position.x, go.body->position.y);
            }
        }
        ImGui::End();
        ImGui::EndFrame();

        ImGui::SFML::Render(window);

        if(doContactRender){
            DebugRenderer::renderContacts();
        }

        if(doVelRender){
            DebugRenderer::renderVelocities();
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
