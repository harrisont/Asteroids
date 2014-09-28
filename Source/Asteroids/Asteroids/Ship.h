#pragma once

#include "Math.h"

class Ship : public sf::Drawable
{
public:
    sf::Vector2f GetCenter() const { return mPosition; }

    void Update(std::chrono::microseconds elapsedTime);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f mPosition;
    sf::Vector2f mVelocity;
    Radians mHeading = 0;
};