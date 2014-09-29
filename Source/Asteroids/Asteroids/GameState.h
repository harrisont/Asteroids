#pragma once

#include "Asteroid.h"
#include "Ship.h"
#include "ParticleEmitter.h"

struct GameState
{
    Ship ship;
    std::vector<Asteroid> asteroids;
    ParticleEmitter particleEmitter;

    GameState();

    GameState(GameState&) = delete;
    GameState& operator=(GameState&) = delete;
};