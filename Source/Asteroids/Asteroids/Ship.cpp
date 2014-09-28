#include "AsteroidsPCH.h"
#include "Ship.h"

#include "CoreLanguage.h"

void Ship::Update(std::chrono::microseconds elapsedTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        const unsigned int kAccelerationMagnitude = 1;
        sf::Vector2f acceleration{ kAccelerationMagnitude * cos(mHeading), kAccelerationMagnitude * sin(mHeading) };
        mVelocity += acceleration;
    }
    
    const Radians kTurnSpeed = kPi / 100;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mHeading -= kTurnSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        mHeading += kTurnSpeed;
    }

    std::chrono::duration<float> elapsedSeconds = elapsedTime;
    mPosition += mVelocity * elapsedSeconds.count();
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    const float kRadius = 40;
    sf::CircleShape shape{ kRadius, 3 };
    shape.setOrigin(kRadius, kRadius);
    shape.setPosition(mPosition);
    shape.setRotation(GetDegrees(mHeading + kPi / 2));
    target.draw(shape);

    // Draw heading
    const float kLineThickness = 4;
    sf::RectangleShape headingLine{ sf::Vector2f{ kRadius, kLineThickness } };
    headingLine.setFillColor(sf::Color::Magenta);
    headingLine.setPosition(mPosition);
    headingLine.setOrigin(0, kLineThickness / 2);
    headingLine.setRotation(GetDegrees(mHeading));
    target.draw(headingLine);

    // Draw velocity
    sf::RectangleShape velocityLine{ sf::Vector2f{ GetMagnitude(mVelocity), kLineThickness } };
    velocityLine.setFillColor(sf::Color::Green);
    velocityLine.setPosition(mPosition);
    velocityLine.setOrigin(0, kLineThickness / 2);
    velocityLine.setRotation(GetDegrees(GetAngle(mVelocity)));
    target.draw(velocityLine);
}