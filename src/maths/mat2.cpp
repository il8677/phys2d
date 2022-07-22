#include <phys2d/maths/mat2.h>

#include <phys2d/maths/vec2.h>

#include <cmath>

namespace phys2d{
    Mat2::Mat2(){
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
    }

    Mat2:: Mat2(std::array<float,4> values){
        v[0] = values[0];
        v[1] = values[1];
        v[2] = values[2];
        v[3] = values[3];
    }

    Mat2::Mat2(float angle){
        setAngle(angle);
    }

    Mat2 Mat2::transposed() const {
        return Mat2({m[0][0], m[1][0], m[0][1], m[1][1]});
    }

    void Mat2::setAngle(float angle){
        float cos = std::cos(angle);
        float sin = std::sin(angle);

        m[0][0] = cos;
        m[0][1] = -sin;
        m[1][0] = sin;
        m[1][1] = cos;
    }

    const Mat2 Mat2::operator*(const Mat2& rhs) const {
        return Mat2({
            m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
            m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
            m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
            m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
        });
    }

    const Vec2 Mat2::operator*(const Vec2& rhs) const{
        return Vec2(m[0][0] * rhs.x + m[0][1] * rhs.y, 
                    m[1][0] * rhs.x + m[1][1] * rhs.y);
    }
}