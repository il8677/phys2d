#include <phys2d/maths/vec2.h>

#include <cmath>

namespace phys2d{
    Vec2::Vec2(float xx, float yy){
        x = xx;
        y = yy;
    }

    Vec2::Vec2(){
        x = 0;
        y = 0;
    }

    Vec2 Vec2::operator -() const {
        return Vec2(-x, -y);
    }

    void Vec2::operator+=(const Vec2& v){
        x += v.x;
        y += v.y;
    }

    void Vec2::operator-=(const Vec2& v){
        x -= v.x;
        y -= v.y;
    }

    void Vec2::operator*=(float s){
        x *= s;
        y *= s;
    }

	Vec2 Vec2::operator+(const Vec2& rhs) const {
        return Vec2(x + rhs.x, y + rhs.y);;
    }

	Vec2 Vec2::operator-(const Vec2& rhs) const {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2 Vec2::operator*(const float rhs) const {
        return Vec2(x*rhs, y*rhs);
    }

    bool Vec2::operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }

    float Vec2::magnitude() const{
        return sqrt(x*x + y*y);
    }
}