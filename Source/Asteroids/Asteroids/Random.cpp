#include "AsteroidsPCH.h"
#include "Random.h"

Random Random::sInstance;

float Random::RandomFloat(const float min, const float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(GetInstance().mRandomEngine);
}

int Random::RandomInt(const int min, const int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(GetInstance().mRandomEngine);
}

unsigned int Random::RandomUnsignedInt(const unsigned int min, const unsigned int max)
{
    std::uniform_int_distribution<unsigned int> distribution(min, max);
    return distribution(GetInstance().mRandomEngine);
}

Random::Random()
    : mRandomEngine(mRandomDevice())
{
}
