#pragma once

#include "ExponentialMovingAverage.h"

struct ViewState
{
    sf::RenderWindow window;
    sf::Font font;
    sf::Text framesPerSecondText;
    ExponentialMovingAverage renderDurationMovingAverage;

    ViewState();

    ViewState(ViewState&) = delete;
    ViewState& operator=(ViewState&) = delete;
};