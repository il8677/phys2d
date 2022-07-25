#include "Renderer.h"

#include <phys2d/Body.h>
#include <phys2d/World.h>
#include <SFML/Graphics.hpp>

#include <memory>

using namespace phys2d;

class GameObject{
    public:

    static GameObject createCircle(World& world, BodyData data, Vec2 pos, float r=1, Body::BodyType type = Body::BodyType::DYNAMIC);
    static GameObject createPoly(World& world, BodyData data, Vec2 pos, std::initializer_list<Vec2> verts, Body::BodyType type = Body::BodyType::DYNAMIC);
    static GameObject createRect(World& world, BodyData data, Vec2 pos, float hextx, float hexty, Body::BodyType type = Body::BodyType::DYNAMIC);
    static GameObject createSquare(World& world, BodyData data, Vec2 pos, float hext=1, Body::BodyType type = Body::BodyType::DYNAMIC);

    void tick(float dt, sf::RenderWindow& window);

    Body* body;

    void destroy();
    bool isDestroyed();

    private:
    bool doDestroy = false;

    GameObject(Body* body, Vec2 pos, std::unique_ptr<Renderer> renderer_);

    std::unique_ptr<Renderer> renderer;
    
};
