#pragma once

namespace phys2d{
	struct Rotation;

	struct Vec2{
		float x, y;

		Vec2(float xx, float yy);
		Vec2(float rotation);
		Vec2();

		// Unary -
		Vec2 operator-() const;	

		void operator+=(const Vec2& v);
		void operator-=(const Vec2& v);
		void operator*=(float s);

		void normalize();
		void zero();

		Vec2 normalized() const;

		// Returns one of the orthogonal vectors
		Vec2 getNormal() const;

		Vec2 operator+(const Vec2& rhs) const;
		Vec2 operator-(const Vec2& rhs) const;
		Vec2 operator*(const float rhs) const;

		float dot(const Vec2& rhs) const;
		
		float cross(const Vec2& rhs) const;
		Vec2 cross(float s) const;


		float magnitude() const;
		float magnitudeSq() const;

		// Returns the angle between the down axis and the vector
		Rotation getAngle() const;

		friend Vec2 operator*(const float lhs, const Vec2 rhs);

		bool operator==(const Vec2& other) const;
		friend bool operator< (const Vec2& v1, const Vec2& v2);
		friend bool operator> (const Vec2& v1, const Vec2& v2);
		friend bool operator<= (const Vec2& v1, const Vec2& v2);
		friend bool operator>= (const Vec2& v1, const Vec2& v2);
	};
}
