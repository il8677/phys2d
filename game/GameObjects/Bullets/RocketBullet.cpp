#include "RocketBullet.h"

#include <Engine/Prefab.h>

#include <phys2d/maths/vec2.h>

RocketBullet::RocketBullet(GameObject* obj, Prefab* projectiles) :  BulletParent(obj, 2.5f, 25, 1){
    projectile = projectiles;
}

void RocketBullet::destroy(){
    const int projectiles = 12;

    float fullRotation = 2 * 3.1415;

    float inc = fullRotation / projectiles;

    for(int i = 0; i < projectiles; i++){
        float angle = inc * i;
        Vec2 dir(angle);

        projectile->create(dir*2 + gameObject->getPosition(), angle);
    }
}