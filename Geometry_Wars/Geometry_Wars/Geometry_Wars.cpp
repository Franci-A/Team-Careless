// Geometry_Wars.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "bullet.h"
#include <iostream>
//#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ChronoSpacer");
	// Initialise everything below
	Bullet* ball = SpawnBall(80, 85, 200, 300, BALL_TYPE::DEFAULT);
	//std::cout << (*ball).X_offset << ".\n" << (*ball).Y_offset << ".\n";
	(*ball).posX = 80;
	(*ball).posY = 80;

	// Game loop
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				Update(&T);
				MoveBall(ball);
			}
		}
		window.clear();
		// Whatever I want to draw goes here
		DisplayBall(&window, ball);
		window.display();
	}

}