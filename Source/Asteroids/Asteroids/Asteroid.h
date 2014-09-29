#pragma once

#include "Math.h"

class Asteroid : public sf::Drawable
{
public:
    void Update(std::chrono::microseconds elapsedTime);

    void SetPosition(sf::Vector2f position) { mPosition = position; }
    void SetVelocity(sf::Vector2f velocity) { mVelocity = velocity; }
    void SetRotationalVelocity(Radians rotationalVelocity) { mRotationalVelocity = rotationalVelocity; }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f mPosition;
    sf::Vector2f mVelocity;
    Radians mRotationalVelocity;
    Radians mHeading = 0;
};