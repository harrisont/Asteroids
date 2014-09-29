#include "AsteroidsPCH.h"

#include "GameState.h"
#include "Time.h"
#include "ViewState.h"

void ProcessWindowEvents(sf::RenderWindow& window, GameState& /*state*/)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Update(GameState& state, std::chrono::microseconds elapsedTime)
{
    state.ship.Update(elapsedTime);

    state.particleEmitter.Update(elapsedTime);
}

void RenderWorld(GameState& gameState, ViewState& viewState, const std::chrono::microseconds /*remainingUpdateTime*/)
{
    // TODO: instead of rendering gameState, render gameState advanced by remainingUpdateTime.

    sf::View view;
    view.setCenter(gameState.ship.GetCenter());
    viewState.window.setView(view);

    viewState.window.draw(gameState.ship);
    viewState.window.draw(gameState.particleEmitter);
}

void RenderUi(GameState& /*gameState*/, ViewState& viewState, const std::chrono::microseconds lastRenderDuration)
{
    viewState.window.setView(viewState.window.getDefaultView());

    viewState.renderDurationMovingAverage.AddSample(FloatSeconds(lastRenderDuration).count());
    const auto framesPerSecond = 1 / std::max(0.001f, viewState.renderDurationMovingAverage.Get());
    viewState.framesPerSecondText.setString(std::to_string(static_cast<unsigned int>(std::roundf(framesPerSecond))) + " FPS");

    viewState.window.draw(viewState.framesPerSecondText);
}

void Render(
    GameState& gameState,
    ViewState& viewState,
    const std::chrono::microseconds lastRenderDuration,
    const std::chrono::microseconds remainingUpdateTime)
{
    viewState.window.clear();
    RenderWorld(gameState, viewState, remainingUpdateTime);
    RenderUi(gameState, viewState, lastRenderDuration);
    viewState.window.display();
}

int main(unsigned int /*argc*/, const char* /*argv*/[])
{
    GameState state;
    ViewState viewState;

    auto previousTime = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds remainingUpdateTime;

    while (viewState.window.isOpen())
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        auto lastRenderDuration(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime));
        previousTime = currentTime;
        remainingUpdateTime += lastRenderDuration;

        ProcessWindowEvents(viewState.window, state);

        const unsigned int kDesiredUdatesPerSecond = 60;
        const auto kUpdateStepDuration = std::chrono::microseconds(1000000) / kDesiredUdatesPerSecond;
        unsigned int updateIterationsPerformedThisFrame = 0;
        while (remainingUpdateTime >= kUpdateStepDuration)
        {
            Update(state, kUpdateStepDuration);
            remainingUpdateTime -= kUpdateStepDuration;

            // Ensure that we don't spiral out of control
            ++updateIterationsPerformedThisFrame;
            if (updateIterationsPerformedThisFrame > kDesiredUdatesPerSecond)
            {
                std::cerr << "Updates are "
                    << std::chrono::duration_cast<std::chrono::milliseconds>(remainingUpdateTime).count()
                    << "ms behind" << std::endl;
                break;
            }
        }

        Render(state, viewState, lastRenderDuration, remainingUpdateTime);
    }

    return 0;
}