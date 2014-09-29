#include "AsteroidsPCH.h"
#include "Asteroid.h"

void Asteroid::Update(std::chrono::microseconds elapsedTime)
{
    std::chrono::duration<float> elapsedSeconds = elapsedTime;
    mPosition += mVelocity * elapsedSeconds.count();
    mHeading += mRotationalVelocity * elapsedSeconds.count();
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    const float kRadius = 40;
    sf::CircleShape shape{ kRadius, 9 };
    shape.setOrigin(kRadius, kRadius);
    shape.setPosition(mPosition);
    shape.setRotation(GetDegrees(mHeading + kPi / 2));
    shape.setFillColor(sf::Color{ 200, 200, 200 });
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