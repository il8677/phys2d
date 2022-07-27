#include "Random.h"

#include "../Input.h"

using namespace phys2d;

bool Random::probability(float probTrue){
    return randFloat(0, 1) < probTrue;
}

int Random::randInt(int min, int max){
    std::uniform_int_distribution<> dist(min, max);

    return dist(generator);
}

float Random::randFloat(float min, float max){
    std::uniform_real_distribution<> dist(min, max);

    return dist(generator);
}


Vec2 Random::randVec(Vec2 min, Vec2 max){
    return Vec2(randFloat(min.x, max.x), randFloat(min.y, max.y));
}

Vec2 Random::randVecInViewport(){
    return Random::randVec(Vec2(10, 10), Vec2(Input::getViewportX()-20, Input::getViewportY()-20));
}

std::mt19937_64 Random::generator;