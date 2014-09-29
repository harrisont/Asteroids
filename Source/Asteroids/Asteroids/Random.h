#pragma once

#include <random>

class Random
{
public:
    static float RandomFloat(const float min, const float max);
    static int RandomInt(const int min, const int max);
    static unsigned int RandomUnsignedInt(const unsigned int min, const unsigned int max);

    Random();

    Random(Random&) = delete;
    Random& operator=(Random&) = delete;

private:
    static Random& GetInstance() { return sInstance; }

    static Random sInstance;
    std::random_device mRandomDevice;
    std::default_random_engine mRandomEngine;
};