#pragma once
#include <random>

#include <phys2d/maths/vec2.h>


class Random{
    public:

    static float randFloat(float min, float max);
    static int randInt(int min, int max);
    static phys2d::Vec2 randVec(phys2d::Vec2 min, phys2d::Vec2 max);
    static phys2d::Vec2 randVecInViewport();

    private:
    static std::mt19937_64 generator;
};