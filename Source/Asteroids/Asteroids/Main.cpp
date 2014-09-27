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

sf::Font LoadFont(const std::string& fontPath)
{
    sf::Font font;
    if (!font.loadFromFile(fontPath))
    {
        std::cerr << "Failed to load font: path=\"" << fontPath << "\"." << std::endl;
    }
    return font;
}

struct UiState
{
    sf::RenderWindow window;
    sf::Font font = LoadFont("Fonts/consola.ttf");
    sf::Text framesPerSecondText;

    UiState()
        : window(sf::VideoMode(800, 800), "Asteroids")
    {
        window.setVerticalSyncEnabled(true);

        framesPerSecondText.setFont(font);
        framesPerSecondText.setCharacterSize(24);
        framesPerSecondText.setColor(sf::Color::White);
    }

    UiState(UiState&) = delete;
    UiState& operator=(UiState&) = delete;
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

void Render(GameState& gameState, UiState& uiState, std::chrono::microseconds elapsedTimeSinceLastRender)
{
    const auto framesPerSecond = static_cast<int>(1 / std::max(0.001f, FloatSeconds(elapsedTimeSinceLastRender).count()));
    uiState.framesPerSecondText.setString(std::to_string(framesPerSecond) + " FPS");

    uiState.window.clear();
    uiState.window.draw(gameState.particleEmitter);
    uiState.window.draw(uiState.framesPerSecondText);
    uiState.window.display();
}

int main(unsigned int /*argc*/, const char* /*argv*/[])
{
    const unsigned int kNumParticles = 5000;
    GameState state{ kNumParticles };

    UiState uiState;

    auto previousTime = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds remainingUpdateTime;

    while (uiState.window.isOpen())
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTimeSinceLastRender(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime));
        previousTime = currentTime;
        remainingUpdateTime += elapsedTimeSinceLastRender;

        ProcessWindowEvents(uiState.window, state);

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

        Render(state, uiState, elapsedTimeSinceLastRender);
    }

    return 0;
}