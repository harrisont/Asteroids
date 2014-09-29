#include "AsteroidsPCH.h"
#include "GameState.h"

namespace
{
    std::vector<Asteroid> CreateAsteroids()
    {
        std::vector<Asteroid> asteroids;

        const unsigned int kNumAsteroids = 10;
        while (asteroids.size() < kNumAsteroids)
        {
            Asteroid asteroid;
            asteroid.SetPosition(sf::Vector2f{ Random::RandomFloat(-1000, 1000), Random::RandomFloat(-1000, 1000) });
            asteroid.SetVelocity(sf::Vector2f{ Random::RandomFloat(-10, 10), Random::RandomFloat(-10, 10) });
            asteroid.SetRotationalVelocity(Random::RandomFloat(-2, 2));
            asteroids.push_back(asteroid);
        }

        return asteroids;
    }
}

GameState::GameState()
    : particleEmitter(5000)
{
    asteroids = CreateAsteroids();
}

void UpdateGameState(GameState& state, std::chrono::microseconds elapsedTime)
{
    for (auto& asteroid : state.asteroids)
    {
        asteroid.Update(elapsedTime);
    }

    state.ship.Update(elapsedTime);

    state.particleEmitter.Update(elapsedTime);
}
