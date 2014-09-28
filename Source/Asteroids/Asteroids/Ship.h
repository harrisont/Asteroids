#pragma once

class Ship : public sf::Drawable
{
public:
    sf::Vector2f GetCenter() const { return position; }

    void Update(std::chrono::microseconds elapsedTime);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f position;
    sf::Vector2f velocity;
};