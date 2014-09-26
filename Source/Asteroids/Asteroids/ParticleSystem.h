#pragma once

struct Particle
{
    sf::Vector2f deltaPositionPerSecond;
    std::chrono::microseconds totalDuration;
    std::chrono::microseconds remainingDuration;
};

class ParticleSystem
{
public:
    ParticleSystem(unsigned int numParticles);
    ParticleSystem(ParticleSystem&) = delete;
    ParticleSystem& operator=(ParticleSystem&) = delete;

    void Update(
        const std::chrono::microseconds elapsedTime,
        std::function<void(Particle&, sf::Vertex&)> resetParticleFunc,
        std::function<void(const std::chrono::microseconds, Particle&, sf::Vertex&)> updateParticleFunc);

    const std::vector<sf::Vertex>& GetParticlePositions() const { return mParticlePositions; };

private:
    std::vector<Particle> mParticles;
    std::vector<sf::Vertex> mParticlePositions;
};

void DrawParticleSystem(const ParticleSystem& system, sf::RenderTarget& target, sf::RenderStates& states);