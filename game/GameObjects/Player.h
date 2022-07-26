#include "Component.h"

class Player : public ComponentParent<Player>{
public:
    Player(GameObject* obj);

    void update(float dt) override;

    private:
    const float moveSpeed = 30.f;
};