#include<iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <phys2d/world.h>
#include <phys2d/body.h>
#include <phys2d/colliders/shape.h>

sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
phys2d::World world;

using namespace phys2d;

class GameObject{
    public:

    GameObject(float mass, Vec2 pos) : circle(50.f){
        circle.setFillColor(sf::Color(150, 50, 250));
        body = world.createBody(std::unique_ptr<Shape>(new Shape()), BodyData(mass));
        body->position = pos;
    }

    void tick(float dt){
        window.draw(circle);
        circle.setPosition(body->position.x, body->position.y);
    }

    private:
    sf::CircleShape circle;
    phys2d::Body* body;
};

int main(){
    GameObject go1(1, Vec2(50, 100));
    GameObject go2(2, Vec2(200, 100));

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        world.step(elapsed.asSeconds());
        go1.tick(elapsed.asSeconds());
        go2.tick(elapsed.asSeconds());

        // end the current frame
        window.display();
    }


    return 0;
}