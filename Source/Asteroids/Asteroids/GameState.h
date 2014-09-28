#pragma once

#include "Ship.h"
#include "ParticleEmitter.h"

struct GameState
{
    Ship ship;
    ParticleEmitter particleEmitter;

    GameState(unsigned int numParticles)
        : particleEmitter(numParticles)
    {
    }

    GameState(GameState&) = delete;
    GameState& operator=(GameState&) = delete;
};