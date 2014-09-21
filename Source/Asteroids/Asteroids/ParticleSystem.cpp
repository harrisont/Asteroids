#include "AsteroidsPCH.h"
#include "ParticleSystem.h"

#include "Time.h"
#include <assert.h>

ParticleSystem::ParticleSystem(unsigned int numParticles)
    : mParticlePositions(numParticles)
    , mParticles(numParticles)
{
}

void ParticleSystem::Update(const std::chrono::microseconds elapsedTime)
{
    assert(mParticles.size() == mParticlePositions.size());

    for (unsigned int i = 0; i < mParticles.size(); ++i)
    {
        auto& particle = mParticles[i];
        auto& vertex = mParticlePositions[i];

        particle.remainingDuration -= elapsedTime;

        if (particle.remainingDuration <= std::chrono::microseconds::zero())
        {
            ResetParticle(particle, vertex);
        }

        std::chrono::duration<float> elapsedSeconds = elapsedTime;
        vertex.position += particle.deltaPositionPerSecond * elapsedSeconds.count();
        vertex.color.a = static_cast<sf::Uint8>(255 * FloatSeconds(particle.remainingDuration).count() / FloatSeconds(particle.totalDuration).count());
    }
}

void ParticleSystem::SetPosition(sf::Vector2f position)
{
    mPosition = position;
}

void ParticleSystem::ResetParticle(ParticleSystem::Particle& particle, sf::Vertex& vertex)
{
    float angle = (std::rand() % 3600) * 3.14159f / 1800.f;
    float speed = (std::rand() % 300) + 50.f;
    particle.deltaPositionPerSecond = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

    particle.remainingDuration = particle.totalDuration = std::chrono::milliseconds(1000 + (std::rand() % 2000));

    vertex.position = mPosition;
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    //states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    target.draw(&mParticlePositions[0], mParticlePositions.size(), sf::Points, states);
}
