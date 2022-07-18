#pragma once

namespace phys2d{
	struct Vec2{
		float x, y;

		Vec2(float xx, float yy);
		Vec2();

		// Unary -
		Vec2 operator-() const;	

		void operator+=(const Vec2& v);
		void operator-=(const Vec2& v);
		void operator*=(float s);

		Vec2 operator+(const Vec2& rhs) const;
		Vec2 operator-(const Vec2& rhs) const;
		Vec2 operator*(const float rhs) const;

		float dot(const Vec2& rhs) const;

		bool operator==(const Vec2& other) const;

		float magnitude() const;
	};
}
