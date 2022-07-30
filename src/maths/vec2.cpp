#include <phys2d/maths/vec2.h>
#include <phys2d/maths/Rotation.h>

#include <cmath>

namespace phys2d{
    Vec2::Vec2(float xx, float yy) : x(xx), y(yy){

    }

    Vec2::Vec2(float rotation){
        x = -sin(rotation);
        y = cos(rotation);
    }

    Vec2::Vec2() : x(0), y(0){
        
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

    void Vec2::normalize(){
        const float m = magnitude();
        
        if(m == 0) return;

        //OPTIMIZATION: Faster than division?

        float minv = 1/m;

        x *= minv;
        y *= minv;
    }

    void Vec2::zero(){
        x = 0;
        y = 0;
    }

    Vec2 Vec2::normalized() const {
        Vec2 v = *this;
        v.normalize();
        return v;
    }

    Vec2 Vec2::getNormal() const{
        return Vec2(y, -x).normalized();
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

    float Vec2::dot(const Vec2& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    float Vec2::cross(const Vec2& rhs) const{
        return x * rhs.y - y * rhs.x;
    }

    Vec2 Vec2::cross(float s) const {
        return Vec2(-s * y, s * x);
    }

    bool Vec2::operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }

    float Vec2::magnitude() const{
        return sqrt(x*x + y*y);
    }

    float Vec2::magnitudeSq() const{
        return x*x + y*y;
    }

    Rotation Vec2::getAngle() const {
        return -Rotation(std::atan2(x, y));
    }

    Vec2 operator*(const float lhs, const Vec2 rhs){
		return Vec2(rhs.x*lhs, rhs.y*lhs);
	}

    bool operator< (const Vec2& v1, const Vec2& v2){
        return v1.magnitudeSq() < v2.magnitudeSq();
    }

    bool operator> (const Vec2& v1, const Vec2& v2){
        return v1.magnitudeSq() > v2.magnitudeSq();
    }

    bool operator<= (const Vec2& v1, const Vec2& v2){
        return v1.magnitudeSq() <= v2.magnitudeSq();
    }
    bool operator>= (const Vec2& v1, const Vec2& v2){
        return v1.magnitudeSq() >= v2.magnitudeSq();
    }
}