#include "Random.h"

using namespace phys2d;

float Random::randFloat(float min, float max){
    std::uniform_real_distribution<> dist(min, max);

    return dist(generator);
}

int Random::randInt(int min, int max){
    std::uniform_int_distribution<> dist(min, max);

    return dist(generator);
}

Vec2 Random::randVec(Vec2 min, Vec2 max){
    return Vec2(randFloat(min.x, max.x), randFloat(min.y, max.y));
}

std::mt19937_64 Random::generator;