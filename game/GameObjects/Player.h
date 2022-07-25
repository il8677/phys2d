#include "Component.h"

class Player : public Component{
public:
    Player(GameObject& obj);

    void update(float dt) override;
    int getID() override;

    private:
    const float moveSpeed = 30.f;
};