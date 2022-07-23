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

#include <phys2d/World.h>
#include <phys2d/colliders/Shape.h>
#include <phys2d/Body.h>
#include "../src/maths/algs.h"

TEST_CASE("SP"){
    World w;
    Body* a = w.createBody(new ShapeCircle(1), BodyData(1));
    Body* b = w.createBody(new ShapeCircle(1), BodyData(1));

    b->position = {3,0};

    SPEntry ae(a, 0);
    SPEntry be(b, 0);


    REQUIRE(ae < be);
    REQUIRE(ae != be);

    REQUIRE(!(ae > be));
    REQUIRE(!(ae == be));

    b->position = {0.9, 0};

    REQUIRE(!(ae < be));
    REQUIRE(!(ae != be));

    REQUIRE(!(ae > be));
    REQUIRE((ae == be));

}
