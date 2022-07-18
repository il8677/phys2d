#include "catch_amalgamated.hpp"
#include <phys2d/maths/vec2.h>

using namespace phys2d;

TEST_CASE("Vector math"){
    const Vec2 a(1,2);
    const Vec2 b(2,3);

    SECTION("ADDITION"){
        Vec2 c = a;
        c += b;
        
        REQUIRE(a + b == Vec2(3,5));
        REQUIRE(b + a == Vec2(3,5));

        REQUIRE(c == a + b);
    }

    SECTION("SUBTRACTION"){
        Vec2 c = a;
        c -= b;

        REQUIRE(a - b == Vec2(-1,-1));
        REQUIRE(b - a == Vec2(1,1));

        REQUIRE(c == a - b);
    }

    SECTION("MULTIPLICATION"){
        REQUIRE(a * 5 == Vec2(5, 10));
    }
}