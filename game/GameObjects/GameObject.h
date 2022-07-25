#pragma once

#include "Renderer.h"

#include <phys2d/Body.h>
#include <phys2d/World.h>
#include <SFML/Graphics.hpp>

#include <memory>

using namespace phys2d;

class GameObject{
    public:
    static std::unique_ptr<GameObject> createRect(World& world, uint32_t color, BodyData data, Vec2 pos, float hextx, float hexty, Body::BodyType type = Body::BodyType::DYNAMIC);

    virtual void tick(float dt, sf::RenderWindow& window);

    Body* body;

    GameObject(Body* body, Vec2 pos, std::unique_ptr<Renderer> renderer_);
    protected:
    private:
    std::unique_ptr<Renderer> renderer;
};
