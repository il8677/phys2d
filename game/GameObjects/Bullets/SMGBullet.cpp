#include "SMGBullet.h"

#include <Engine/GameObject.h>

SMGBullet::SMGBullet(GameObject* obj, int count_) : count(count_), BulletParent(obj, getFireRate(), 45, 4){

}

void SMGBullet::onClone(Component* clone) {
    SMGBullet* c = (SMGBullet*)clone;

    c->count = count++;
}

float SMGBullet::getFireRate(){
    if(count % 3 == 0) return 1.25f;
    return 0.1f;
}