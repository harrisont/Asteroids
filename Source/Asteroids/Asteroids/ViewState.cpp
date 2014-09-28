#include "AsteroidsPCH.h"
#include "ViewState.h"

namespace
{
    sf::Font LoadFont(const std::string& fontPath)
    {
        sf::Font font;
        if (!font.loadFromFile(fontPath))
        {
            std::cerr << "Failed to load font: path=\"" << fontPath << "\"." << std::endl;
        }
        return font;
    }
}

ViewState::ViewState()
    : window(sf::VideoMode(800, 800), "Asteroids")
    , font(LoadFont("Fonts/consola.ttf"))
    , renderDurationMovingAverage(0.1f /*decayRate*/)
{
    window.setVerticalSyncEnabled(true);

    framesPerSecondText.setFont(font);
    framesPerSecondText.setCharacterSize(24);
    framesPerSecondText.setColor(sf::Color::White);
}