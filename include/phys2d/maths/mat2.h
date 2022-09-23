#pragma once
#include <array>

namespace phys2d{
    struct Vec2;

    struct Mat2{
        union {
            float m[2][2];
            float v[4];
        };

        Mat2();
        Mat2(std::array<float,4> values);

        // Generates rotation matrix for angle
        Mat2(float angle);

        Mat2 transposed() const;

        void setAngle(float angle);

        const Mat2 operator*(const Mat2& rhs) const;
        const Vec2 operator*(const Vec2& rhs) const;
    };
}