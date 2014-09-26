#include "AsteroidsPCH.h"
#include "ParticleEmitter.h"

#include "Time.h"

ParticleEmitter::ParticleEmitter(unsigned int numParticles)
    : mParticleSystem(numParticles)
{
}

void ParticleEmitter::Update(const std::chrono::microseconds elapsedTime)
{
    using namespace std::placeholders;
    mParticleSystem.Update(
        elapsedTime,
        std::bind(&ParticleEmitter::ResetParticle, this, _1, _2),
        std::bind(&ParticleEmitter::UpdateParticle, this, _1, _2, _3));
}

void ParticleEmitter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawParticleSystem(mParticleSystem, target, states);
}

void ParticleEmitter::ResetParticle(Particle& particle, sf::Vertex& vertex)
{
    float angle = (std::rand() % 3600) * 3.14159f / 1800.f;
    float speed = (std::rand() % 300) + 20.f;
    particle.deltaPositionPerSecond = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

    particle.remainingDuration = particle.totalDuration = std::chrono::milliseconds(500 + (std::rand() % 1000));
     
    vertex.position = mPosition;
}

void ParticleEmitter::UpdateParticle(const std::chrono::microseconds elapsedTime, Particle& particle, sf::Vertex& vertex)
{
    particle.deltaPositionPerSecond *= 0.995f;

    std::chrono::duration<float> elapsedSeconds = elapsedTime;
    vertex.position += particle.deltaPositionPerSecond * elapsedSeconds.count();

    vertex.color.a = static_cast<sf::Uint8>(255 * FloatSeconds(particle.remainingDuration).count() / FloatSeconds(particle.totalDuration).count());
}