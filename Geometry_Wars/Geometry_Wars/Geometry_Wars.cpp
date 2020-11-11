// Geometry_Wars.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "bullet.cpp"
#include <iostream>
#include <SFML/Graphics.hpp>
extern TIME T;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ChronoSpacer");
	// Initialise everything below
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Time : " << T.time << ".\n";
	}
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