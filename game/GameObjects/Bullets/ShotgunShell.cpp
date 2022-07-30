#include "ShotgunShell.h"

#include "../util/Random.h"

#include <Engine/Prefab.h>
#include <phys2d/maths/vec2.h>

ShotgunShell::ShotgunShell(GameObject* obj, Prefab* projectiles) :  BulletParent(obj, 2.f, 25, 0){
    projectile = projectiles;
}

void ShotgunShell::update(float dt){
    const int projectiles = 6;

    float cone = 3.1415 / 8 + Random::randFloat(-3.1415/12, 3.1415/12);

    for(int i = 0; i < projectiles; i++){
        float angle = Random::randFloat(-cone, cone) + gameObject->getRotation();

        Vec2 dir(angle);

        GameObject& obj = projectile->create(dir*5 + gameObject->getPosition(), angle);
        obj.getComponent<BodyComponent>()->body->angularVel = angle;
    }
    gameObject->destroy();
}