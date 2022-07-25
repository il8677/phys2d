#include "Renderer.h"

#include <cmath>

#include <random>

void CircleRenderer::render(RenderInfo ri, sf::RenderWindow& window){
    circle.setRadius(r);
    circle.setOrigin(r, r);
    circle.setRotation(ri.rot * 180 / 3.14159265);
    circle.setPosition(ri.p.x, ri.p.y);
    circle.setFillColor(color);
/*    sf::Vertex line[2] = {
        sf::Vertex(sf::Vector2f(ri.p.x, ri.p.y)),
        sf::Vertex(sf::Vector2f(ri.p.x + r*std::sin(ri.p.x), ri.p.y + r * std::cos(ri.p.x)))
    };

    window.draw(line, 2, sf::Lines);*/

    window.draw(circle);
}

CircleRenderer::CircleRenderer(float r_, uint32_t color_) : r(r_){
    color = sf::Color(color_);
    if(init){
        init = false;
    }
}

bool CircleRenderer::init = true;
sf::CircleShape CircleRenderer::circle;

void PolyRenderer::render(RenderInfo ri, sf::RenderWindow& window){
    shape.setPosition(ri.p.x, ri.p.y);
    shape.setRotation(ri.rot * 180 / 3.14159265);
    shape.setFillColor(color);

    window.draw(shape);
}

PolyRenderer::PolyRenderer(std::initializer_list<Vec2> verts, uint32_t color_) {
    color = sf::Color(color_);
    
    int i = 0;

    setupShape();

    shape.setPointCount(verts.size());

    for(auto it = verts.begin(); it != verts.end(); it++){
        shape.setPoint(i, sf::Vector2f(it->x, it->y));
        i++;
    }
}

PolyRenderer::PolyRenderer(std::vector<Vec2> verts, uint32_t color_) {
    color = sf::Color(color_);

    int i = 0;

    setupShape();

    shape.setPointCount(verts.size());
    
    for(auto it = verts.begin(); it != verts.end(); it++){
        shape.setPoint(i, sf::Vector2f(it->x, it->y));
        i++;
    }
}

void PolyRenderer::setupShape(){
    shape.setOutlineColor(sf::Color(rand()%255, rand()%255, rand()%255));
    shape.setOutlineThickness(0.01);
    shape.setFillColor(sf::Color(rand()%255, rand()%255, rand()%255, 200));
}
