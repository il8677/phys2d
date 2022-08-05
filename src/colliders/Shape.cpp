#include <phys2d/colliders/Shape.h>

#include<algorithm>
#include <float.h>

namespace phys2d{
    Shape::Shape(Shape::Type type_, float maxExtent_) :
        type(type_), maxExtent(maxExtent_) {

    }

    ShapePoly::ShapePoly(std::initializer_list<Vec2> points_) : 
        Shape(Shape::Type::POLY, std::max(points_).magnitude()), 
        points(points_),
        normals(std::move(calculateNormals())) {
        
    }

    ShapePoly::ShapePoly(float halfext) : 
        Shape(Shape::Type::POLY, halfext), 
        points(std::move(getPoints(halfext, halfext))),
        normals(std::move(calculateNormals())) {
    }

    ShapePoly::ShapePoly(float halfextX, float halfextY) : 
        Shape(Shape::Type::POLY, std::max(halfextX, halfextY)),
        points(std::move(getPoints(halfextX, halfextY))),
        normals(std::move(calculateNormals())){
        
    }

    Vec2 ShapePoly::getMaxPoint(Vec2 dir) const {
        float bestProj = -FLT_MAX;
        Vec2 bestPoint;

        for(const Vec2& point : points){
            float projection = point.dot(dir);

            if(projection > bestProj){
                bestPoint = point;
                bestProj = projection;
            }
        }

        return bestPoint;
    }

    std::vector<Vec2> ShapePoly::getPoints(std::initializer_list<Vec2> points_){
        std::vector<Vec2> points__;
        points__.insert(points.begin(), points_.end(), points_.end());

        return points__;
    }

    std::vector<Vec2> ShapePoly::getPoints(float halfextX, float halfextY){
        std::vector<Vec2> points__;

        points__.resize(4);
        points__[0] = Vec2(-halfextX, -halfextY);
        points__[1] = Vec2(halfextX, -halfextY);
        points__[2] = Vec2(halfextX, halfextY);
        points__[3] = Vec2(-halfextX, halfextY);

        return points__;
    }

    std::vector<Vec2> ShapePoly::calculateNormals(){
        std::vector<Vec2> normals_(points.size());

        for(int i = 0; i < points.size(); i++){
            int nextVert = i+1;
            if(nextVert == points.size()) nextVert = 0;

            Vec2 face = points[nextVert] - points[i];

            normals_[i] = face.getNormal();
        }

        return normals_;
    }

    Shape* ShapePoly::clone(){
        return new ShapePoly(*this);
    }

    Shape* ShapeCircle::clone(){
        return new ShapeCircle(*this);
    }

    ShapeCircle::ShapeCircle(float radius_) :
        Shape(Shape::Type::CIRCLE, radius_), radius(radius_) {
        
    }
}