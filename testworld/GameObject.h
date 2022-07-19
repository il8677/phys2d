#include <phys2d/Body.h>
#include <phys2d/World.h>
#include <SFML/Graphics.hpp>

#include <memory>

using namespace phys2d;

class GameObject{
    public:

    static GameObject createCircle(World& world, BodyData data, Vec2 pos, float r=1);
    
    void tick(float dt, sf::RenderWindow& window);

    Body* body;

    private:
    GameObject(Body* body, Vec2 pos);

    std::unique_ptr<sf::Shape> renderable;
};
