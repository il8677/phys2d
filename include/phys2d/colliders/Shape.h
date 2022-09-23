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
        float maxExtent; // The maximum distance between the COM and the edge of the objedt

        virtual Shape* clone()=0; // Returns a pointer to a copy of the object

        protected:
        Shape(Type type, float maxExtent);
    };

    struct ShapePoly : Shape {
        ShapePoly(std::initializer_list<Vec2> points);

        ShapePoly(float halfext=1.f); // Square
        ShapePoly(float halfextX, float halfextY); // Rect

        const std::vector<Vec2> points; 
        const std::vector<Vec2> normals; // The face normals for the face composed of the points i - i + 1

        Vec2 getMaxPoint(Vec2 dir) const; // Returns the point thats the furthest out in the direction dir

        Shape* clone() override;

        private:
        std::vector<Vec2> getPoints(std::initializer_list<Vec2> points_); // Used by the constructor to get the points for the body
        std::vector<Vec2> getPoints(float halfextX, float halfextY);

        std::vector<Vec2> calculateNormals(); // Used by the constructor to get normals for the body
    };

    struct ShapeCircle : Shape {
        ShapeCircle(float radius);

        Shape* clone() override;

        const float radius;
    };
}