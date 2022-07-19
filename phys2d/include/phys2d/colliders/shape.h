#pragma once
#include <phys2d/maths/vec2.h>

#include <vector>
#include <initializer_list>

namespace phys2d{
    struct Shape{
        enum Type{
            CIRCLE=0, POLY=1
        };


        const Type type;
        protected:
        Shape(Type type);
    };

    struct ShapePoly : Shape {
        ShapePoly(std::initializer_list<Vec2> points);
        ShapePoly(float halfext=1.f); // Square
        ShapePoly(float halfextX, float halfextY); // Rect

        std::vector<Vec2> points; // OPTIMIZATION: data structure
    };

    struct ShapeCircle : Shape {
        ShapeCircle(float radius);

        float radius;
    };
}