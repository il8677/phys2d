#include <phys2d/maths/rotation.h>

namespace phys2d{
    Rotation::Rotation(float a) : angle(a) {

    }
    

    Rotation::Rotation() : angle(0) {
        
    }

    Rotation::operator float&(){
        return angle;
    }

}