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
        const float maxExtent;

        protected:
        Shape(Type type, float maxExtent);
    };

    struct ShapePoly : Shape {
        ShapePoly(std::initializer_list<Vec2> points);
        ShapePoly(float halfext=1.f); // Square
        ShapePoly(float halfextX, float halfextY); // Rect

        const std::vector<Vec2> points; // OPTIMIZATION: data structure
        const std::vector<Vec2> normals;

        Vec2 getMaxPoint(Vec2 dir) const;

        private:
        std::vector<Vec2> getPoints(std::initializer_list<Vec2> points_);
        std::vector<Vec2> getPoints(float halfextX, float halfextY);

        std::vector<Vec2> calculateNormals();
    };

    struct ShapeCircle : Shape {
        ShapeCircle(float radius);

        const float radius;
    };
}