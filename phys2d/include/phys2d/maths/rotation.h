

namespace phys2d{
    struct Rotation{
        Rotation(float angle);
        Rotation();

        operator float&();

        float angle;
    };
}