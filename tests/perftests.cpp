#include "catch_amalgamated.hpp"

#include "phys2d/World.h"

#include <cmath>

TEST_CASE("10,000 spheres") {

    BENCHMARK_ADVANCED("1 step")(Catch::Benchmark::Chronometer meter) {
        phys2d::World world(0);

        for (size_t x = 0; x < 100; x++) {
            for (size_t y = 0; y < 100; y++) {
                phys2d::Body* body = world.createBody(new ShapeCircle{0.5}, BodyData{1});
                body->position = {static_cast<float>(x), static_cast<float>(y)};
                body->velocity = {static_cast<float>(std::sin(x)), static_cast<float>(std::cos(y))};
            }
        }

        world.createBody(new ShapePoly(0.25f,51.f), BodyData{0, 1}, Body::BodyType::STATIC)->position = {-1, 50};
        world.createBody(new ShapePoly(0.25f,51.f), BodyData{0, 1}, Body::BodyType::STATIC)->position = {101, 50};
        world.createBody(new ShapePoly(51.f,0.25f), BodyData{0, 1}, Body::BodyType::STATIC)->position = {50, -1};
        world.createBody(new ShapePoly(51.f,0.25f), BodyData{0, 1}, Body::BodyType::STATIC)->position = {50, 101};

        meter.measure([&] {
            for (size_t i = 0; i < 1; i++)
                world.step(0.1);
        });

        world.clear();
    };
}