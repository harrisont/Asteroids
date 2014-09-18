// Ignore SFML warnings.
#pragma warning(push, 0)
// Setting the warning level to 1 doesn't disable C4350 for some reason, so explicitly disable it.
#pragma warning(disable : 4350)
#include <SFML/Graphics.hpp>
#pragma warning(pop)

int main(unsigned int /*argc*/, const char* /*argv*/[])
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}