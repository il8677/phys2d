#include <phys2d/colliders/Shape.h>

namespace phys2d{
    Shape::Shape(Shape::Type type_) :
        type(type_) {

    }

    ShapePoly::ShapePoly(std::initializer_list<Vec2> points_) : 
        Shape(Shape::Type::POLY) {
        points.insert(points.end(), points_.begin(), points_.end());
    }

    ShapePoly::ShapePoly(float halfext) : 
        Shape(Shape::Type::POLY) {
        points.resize(4);
        points[0] = Vec2(-halfext, -halfext);
        points[1] = Vec2(-halfext, halfext);
        points[2] = Vec2(halfext, halfext);
        points[3] = Vec2(halfext, -halfext);
    }

    ShapePoly::ShapePoly(float halfextX, float halfextY) : 
        Shape(Shape::Type::POLY) {
        points.resize(4);
        points[0] = Vec2(-halfextX, -halfextY);
        points[1] = Vec2(-halfextX, halfextY);
        points[2] = Vec2(halfextX, halfextY);
        points[3] = Vec2(halfextX, -halfextY);
    }

    ShapeCircle::ShapeCircle(float radius_) :
        Shape(Shape::Type::CIRCLE), radius(radius_) {
        
    }
}