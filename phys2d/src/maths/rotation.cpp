#include <phys2d/maths/Rotation.h>

namespace phys2d{
    Rotation::Rotation(float a) : angle(a) {

    }
    

    Rotation::Rotation() : angle(0) {
        
    }

    Rotation::operator float&(){
        return angle;
    }

}