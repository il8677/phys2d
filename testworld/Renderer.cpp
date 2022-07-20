#include "Renderer.h"

void CircleRenderer::render(RenderInfo ri, sf::RenderWindow& window){
    circle.setRadius(r);
    circle.setOrigin(r, r);
    circle.setPosition(ri.p.x, ri.p.y);
    window.draw(circle);
}

CircleRenderer::CircleRenderer(float r_) : r(r_){
    if(init){
        init = false;
        circle.setFillColor(sf::Color(150, 50, 250));
    }
}

bool CircleRenderer::init = true;
sf::CircleShape CircleRenderer::circle;

void PolyRenderer::render(RenderInfo ri, sf::RenderWindow& window){
    shape.setPosition(ri.p.x, ri.p.y);

    window.draw(shape);
}

PolyRenderer::PolyRenderer(std::initializer_list<Vec2> verts) {
    int i = 0;

    shape.setFillColor(sf::Color(56, 94, 156));
    shape.setPointCount(verts.size());

    for(auto it = verts.begin(); it != verts.end(); it++){
        shape.setPoint(i, sf::Vector2f(it->x, it->y));
        i++;
    }
}

PolyRenderer::PolyRenderer(std::vector<Vec2> verts) {
    int i = 0;

    shape.setFillColor(sf::Color(56, 94, 156));

    shape.setPointCount(verts.size());
    
    for(auto it = verts.begin(); it != verts.end(); it++){
        shape.setPoint(i, sf::Vector2f(it->x, it->y));
        i++;
    }
}
