#include "AsteroidsPCH.h"

#include "ParticleEmitter.h"
#include "Time.h"

struct GameState
{
    ParticleEmitter particleEmitter;

    GameState(unsigned int numParticles)
        : particleEmitter(numParticles)
    {
    }

    GameState(GameState&) = delete;
    GameState& operator=(GameState&) = delete;
};

void ProcessWindowEvents(sf::RenderWindow& window, GameState& state)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    state.particleEmitter.SetPosition(window.mapPixelToCoords(mousePosition));
}

void Update(GameState& state, std::chrono::microseconds elapsedTime)
{
    state.particleEmitter.Update(elapsedTime);
}

void Render(sf::RenderWindow& window, GameState& state)
{
    window.clear();
    window.draw(state.particleEmitter);
    window.display();
}

int main(unsigned int /*argc*/, const char* /*argv*/[])
{
    const unsigned int kNumParticles = 5000;
    GameState state{ kNumParticles };

    sf::RenderWindow window(sf::VideoMode(800, 800), "Asteroids");
    window.setVerticalSyncEnabled(true);

    auto previousTime = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds remainingUpdateTime;

    while (window.isOpen())
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime));
        previousTime = currentTime;
        remainingUpdateTime += elapsedTime;

        ProcessWindowEvents(window, state);

        const unsigned int kDesiredUdatesPerSecond = 60;
        const auto kUpdateStepDuration = std::chrono::microseconds(1000000) / kDesiredUdatesPerSecond;
        unsigned int updateIterations = 0;
        while (remainingUpdateTime >= kUpdateStepDuration)
        {
            Update(state, kUpdateStepDuration);
            remainingUpdateTime -= kUpdateStepDuration;

            // Ensure that we don't spiral out of control
            ++updateIterations;
            if (updateIterations > kDesiredUdatesPerSecond)
            {
                std::cerr << "Updates are "
                    << std::chrono::duration_cast<std::chrono::milliseconds>(remainingUpdateTime).count()
                    << "ms behind" << std::endl;
                break;
            }
        }

        Render(window, state);

        std::cout << kNumParticles << " particles"
            << ", " << static_cast<int>(1 / std::max(0.001f, FloatSeconds(elapsedTime).count())) << " FPS"
            << std::endl;
    }

    return 0;
}