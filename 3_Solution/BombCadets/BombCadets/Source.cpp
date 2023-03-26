#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace std;

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();

        // Draw
        sf::CircleShape circle;
        circle.setFillColor(sf::Color::Red);
        circle.setRadius(100.0f);
        circle.setScale(sf::Vector2f(1.0f, 1.0f));

        window.draw(circle);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}