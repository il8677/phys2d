#pragma once

#include <phys2d/maths/vec2.h>
#include <phys2d/maths/Rotation.h>
#include <SFML/Graphics.hpp>

using namespace phys2d;

struct RenderInfo{
    Vec2 p;
    Rotation rot;
};

class Renderer{
    public:
    virtual void render(RenderInfo ri, sf::RenderWindow& window)=0;
    protected:
    sf::Color color;
};

class CircleRenderer : public Renderer {
    public:
    void render(RenderInfo ri, sf::RenderWindow& window) override;

    CircleRenderer(float r, uint32_t color);

    private:
    static sf::CircleShape circle;
    static bool init;

    float r;
};

class PolyRenderer : public Renderer{
    public:
    void render(RenderInfo ri, sf::RenderWindow& window) override;

    PolyRenderer(std::initializer_list<Vec2> points, uint32_t color);
    PolyRenderer(std::vector<Vec2> points, uint32_t color);

    private:
    void setupShape();

    sf::ConvexShape shape;
};