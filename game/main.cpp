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



int main(){
    // SFML setup
    window.setFramerateLimit(60);
    window.setView(mainView);

    std::vector<GameObject> objects;

    // IMGUI debug
    ImGui::SFML::Init(window);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    
    
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

        ImGui::SFML::Render(window);

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
