#include "PistolBullet.h"

#include <Engine/GameObject.h>
#include <Engine/BodyComponent.h>


PistolBullet::PistolBullet(GameObject* obj) : BulletParent(obj, 1, 40, 4){

}
