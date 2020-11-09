// Geometry_Wars.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ChronoSpacer");
	// Initialise everything below
	// Game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		// Whatever I want to draw goes here
		window.display();
	}

}