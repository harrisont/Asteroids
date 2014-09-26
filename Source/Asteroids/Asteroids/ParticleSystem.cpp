#include "AsteroidsPCH.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int numParticles)
    : mParticlePositions(numParticles)
    , mParticles(numParticles)
{
}

void ParticleSystem::Update(
    const std::chrono::microseconds elapsedTime,
    std::function<void(Particle&, sf::Vertex&)> resetParticleFunc,
    std::function<void(const std::chrono::microseconds, Particle&, sf::Vertex&)> updateParticleFunc)
{
    assert(mParticles.size() == mParticlePositions.size());

    for (unsigned int i = 0; i < mParticles.size(); ++i)
    {
        auto& particle = mParticles[i];
        auto& vertex = mParticlePositions[i];

        particle.remainingDuration -= elapsedTime;

        if (particle.remainingDuration <= std::chrono::microseconds::zero())
        {
            resetParticleFunc(particle, vertex);
        }
        else
        {
            updateParticleFunc(elapsedTime, particle, vertex);
        }
    }
}

void DrawParticleSystem(const ParticleSystem& system, sf::RenderTarget& target, sf::RenderStates& states)
{

    // apply the transform
    //states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    const auto& particlePositions = system.GetParticlePositions();
    target.draw(&particlePositions[0], particlePositions.size(), sf::Points, states);
}