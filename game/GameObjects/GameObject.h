#pragma once

#include "Renderer.h"

#include <phys2d/Body.h>
#include <phys2d/World.h>
#include <SFML/Graphics.hpp>

#include <memory>

using namespace phys2d;

class GameObject{
    public:

    virtual void tick(float dt, sf::RenderWindow& window);

    Body* body;

    protected:
    GameObject(Body* body, Vec2 pos, std::unique_ptr<Renderer> renderer_);
    private:
    std::unique_ptr<Renderer> renderer;
};
