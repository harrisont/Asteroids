#include "AsteroidsPCH.h"
#include "Ship.h"

void Ship::Update(std::chrono::microseconds elapsedTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        const unsigned int kAccelerationMagnitude = 10;
        sf::Vector2f acceleration{ kAccelerationMagnitude * cosf(mHeading), kAccelerationMagnitude * sinf(mHeading) };
        mVelocity += acceleration;
    }

    std::chrono::duration<float> elapsedSeconds = elapsedTime;
    mPosition += mVelocity * elapsedSeconds.count();
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    sf::CircleShape shape{ 40, 3 };
    shape.setOrigin(40, 40);
    shape.setPosition(mPosition);
    target.draw(shape);
}