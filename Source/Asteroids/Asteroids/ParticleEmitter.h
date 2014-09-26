#pragma once

#include "ParticleSystem.h"

class ParticleEmitter : public sf::Drawable
{
public:
    ParticleEmitter(unsigned int numParticles);
    ParticleEmitter(ParticleEmitter&) = delete;
    ParticleEmitter& operator=(ParticleEmitter&) = delete;

    void Update(const std::chrono::microseconds elapsedTime);
    void SetPosition(sf::Vector2f position) { mPosition = position; }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void ResetParticle(Particle& particle, sf::Vertex& vertex);
    void UpdateParticle(const std::chrono::microseconds elapsedTime, Particle& particle, sf::Vertex& vertex);

    ParticleSystem mParticleSystem;
    sf::Vector2f mPosition;
};