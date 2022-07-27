#include <Engine/Component.h>

class Gun;
class Prefab;

class Player : public ComponentParent<Player>{
public:
    Player(GameObject* obj, Gun* gun);

    void update(float dt) override;

    void setBulletPrefab(Prefab* prefab);

    private:
    const float moveSpeed = 30.f;

    Gun* gun;
};