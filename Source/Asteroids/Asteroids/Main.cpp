#include "AsteroidsPCH.h"

#include "ParticleSystem.h"
#include "Time.h"
#include <iostream>

int main(unsigned int /*argc*/, const char* /*argv*/[])
{
    const unsigned int kNumParticles = 100000;
    ParticleSystem particles(kNumParticles);

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    auto previousUpdateTime = std::chrono::high_resolution_clock::now();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        particles.SetPosition(window.mapPixelToCoords(mousePosition));

        auto updateTime = std::chrono::high_resolution_clock::now();
        auto timeDelta = updateTime - previousUpdateTime;
        auto elapsedTime(std::chrono::duration_cast<std::chrono::microseconds>(timeDelta));
        previousUpdateTime = updateTime;

        particles.Update(elapsedTime);

        window.clear();
        window.draw(particles);
        window.display();

        std::cout << particles.GetNumParticles() << " particles"
            << ", " << static_cast<int>(1 / std::max(0.001f, FloatSeconds(elapsedTime).count())) << " FPS"
            << std::endl;
    }

    return 0;
}