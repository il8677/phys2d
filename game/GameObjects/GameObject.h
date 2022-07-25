#pragma once

#include "Renderer.h"
#include "Component.h"

#include <phys2d/Body.h>
#include <phys2d/World.h>
#include <SFML/Graphics.hpp>

#include <memory>
#include <functional>

using namespace phys2d;

class Game;

class GameObject{
    public:
    static GameObject createCircle(World& world, uint32_t color, BodyData data, Vec2 pos, float r, Body::BodyType type);
    static GameObject createRect(World& world, uint32_t color, BodyData data, Vec2 pos, float hextx, float hexty, Body::BodyType type = Body::BodyType::DYNAMIC);

    void setup();
    void tick(float dt, sf::RenderWindow& window);

    GameObject( std::unique_ptr<Renderer> renderer_);

    static GameObject& addObject(GameObject&& go);

    template <class T, typename... Args>
    T* addComponent(Args&&... args){
        return static_cast<T*>(
            components.emplace_back(
                std::make_unique<T>(*this, std::forward<Args>(args)...)).get());
    }

    template <class T>
    T* getComponent(){
        int targetID = Component::getID<T>();
        for(std::unique_ptr<Component>& component : components){
            if(component->getID() == targetID) 
                return static_cast<T*>(component.get());
        }

        return nullptr;
    }

    Vec2 getPosition();
    Vec2 getVelocity();
    float getRotation();

    protected:
    std::vector<std::unique_ptr<Component>> components;
    private:
    std::unique_ptr<Renderer> renderer;

    static std::list<GameObject> objects;

    friend class Game;
};
