#pragma once

namespace phys2d{
    
    // Wrapper around a float, in case future operators are needed
    struct Rotation{
        Rotation(float angle);
        Rotation();

        operator float&();

        float angle;
    };
}