#include "GameObject.h"

class Player : public GameObject{
public:
    Player(World& world, Vec2 pos);

    void tick(float dt, sf::RenderWindow& window) override;

    private:
    const float moveSpeed = 25.f;
};