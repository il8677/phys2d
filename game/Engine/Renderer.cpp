#include <Engine/Renderer.h>

#include <cmath>

#include <random>

void Renderer::setColor(uint32_t c){
    color = sf::Color(c);
}

uint32_t Renderer::getColor(){
    return color.toInteger();
}


void NullRenderer::render(RenderInfo ri, sf::RenderWindow& window){

}

Renderer* NullRenderer::clone(){
    return new NullRenderer(*this);
}

void CircleRenderer::render(RenderInfo ri, sf::RenderWindow& window){
    circle.setRadius(r);
    circle.setOrigin(r, r);
    circle.setRotation(ri.rot * 180 / 3.14159265);
    circle.setPosition(ri.p.x, ri.p.y);
    circle.setFillColor(color);

    window.draw(circle);
}

CircleRenderer::CircleRenderer(float r_, uint32_t color_) : r(r_){
    color = sf::Color(color_);
}

Renderer* CircleRenderer::clone(){
    return new CircleRenderer(*this);
}

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
    shape.setFillColor(sf::Color(rand()%255, rand()%255, rand()%255, 200));
}

Renderer* PolyRenderer::clone(){
    return new PolyRenderer(*this);
}