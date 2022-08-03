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
    virtual Renderer* clone()=0;

    void setColor(uint32_t c);
    uint32_t getColor();
    
    protected:
    sf::Color color;
};

class NullRenderer : public Renderer{
    void render(RenderInfo ri, sf::RenderWindow& window) override;
    Renderer* clone() override;
};

class CircleRenderer : public Renderer {
    public:
    void render(RenderInfo ri, sf::RenderWindow& window) override;
    Renderer* clone() override;

    CircleRenderer(float r, uint32_t color);

    private:
    static sf::CircleShape circle;

    float r;
};

class PolyRenderer : public Renderer{
    public:
    void render(RenderInfo ri, sf::RenderWindow& window) override;
    Renderer* clone() override;

    PolyRenderer(std::initializer_list<Vec2> points, uint32_t color);
    PolyRenderer(std::vector<Vec2> points, uint32_t color);

    private:
    void setupShape();

    sf::ConvexShape shape;
};