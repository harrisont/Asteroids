#include "AsteroidsPCH.h"
#include "Ship.h"

void Ship::Update(std::chrono::microseconds elapsedTime)
{
    std::chrono::duration<float> elapsedSeconds = elapsedTime;
    position += velocity * elapsedSeconds.count();
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    sf::CircleShape shape{ 40, 3 };
    shape.setOrigin(40, 40);
    shape.setPosition(position);
    target.draw(shape);
}