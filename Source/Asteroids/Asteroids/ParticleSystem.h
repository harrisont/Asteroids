#pragma once

#include <chrono>

class ParticleSystem : public sf::Drawable
{
public:
    ParticleSystem(unsigned int numParticles);

    void Update(const std::chrono::microseconds elapsedTime);
    //void AddParticle(const sf::Vector2f position, const sf::Vector2f deltaPositionPerSecond, const std::chrono::milliseconds duration);
    void SetPosition(sf::Vector2f position);
    unsigned int GetNumParticles() const { return mParticles.size(); };

private:
    struct Particle
    {
        sf::Vector2f deltaPositionPerSecond;
        std::chrono::microseconds totalDuration;
        std::chrono::microseconds remainingDuration;
    };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void ResetParticle(Particle& particle, sf::Vertex& vertex);

    std::vector<Particle> mParticles;
    std::vector<sf::Vertex> mParticlePositions;
    sf::Vector2f mPosition;
};