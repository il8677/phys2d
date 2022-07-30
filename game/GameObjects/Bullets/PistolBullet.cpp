#include "PistolBullet.h"

#include <Engine/GameObject.h>
#include <Engine/BodyComponent.h>


PistolBullet::PistolBullet(GameObject* obj, float damage) : BulletParent(obj, 1, 40, damage){

}
