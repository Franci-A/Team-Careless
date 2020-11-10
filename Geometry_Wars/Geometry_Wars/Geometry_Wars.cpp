// Geometry_Wars.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>

#include "Enemy.h"
#include "ScreenResolution.h"
#include "Timer.h"

using namespace std;
using namespace sf;

int main()
{

	RectangleShape rectangle(Vector2f(100, 50));
	#pragma region Screen Resolution
		int width = 0;
		int height = 0;
		GetDesktopResolution(width, height);
	#pragma endregion 
	#pragma region Shape
		vector<string> shapeVect{
			"Circle",
			"Triangle",
			"Square",
			"Pentagon",
			"Hexagon",
			"Heptagon",
			"Octagon",
			"Enneagone",
			"Decagone",
		};
	#pragma endregion
	#pragma region Enemy
		vector<CircleShape> enemyVect;
	#pragma endregion
	#pragma region RNG
		srand(time(NULL));
		int rng = rand() % 100 + 10;
		int rngShape = rand() % shapeVect.size();
		int rngRadius = rand() % 50 + 10;
		int rngWidth = rand() % width;
		int rngHeight = rand() % height;
		int rngWallSpawn = rand() % 4 + 1;
		int rngColor = rand() % 7 + 1;
	#pragma endregion 
	#pragma region Timer
		Timer timer;
		timer.start();
		float spawnTime = 1.0f;
	#pragma endregion


	//VideoMode DesktopMode = VideoMode::GetDesktopMode();
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window", Style::Fullscreen);
	// Initialise everything below
	// Game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
			}
		}

		window.clear();

		#pragma region Update RNG
			srand(time(NULL));
			rng = rand() % 100 + 10;
			rngWidth = rand() % width;
			rngHeight = rand() % height;
			rngShape = rand() % (shapeVect.size() - 1);
			rngRadius = rand() % 50 + 10;
			rngWallSpawn = rand() % 4 + 1;
			rngColor = rand() % 7 + 1;
		#pragma endregion 
		#pragma region Spawn Enemy
			if (timer.elapsedSeconds() > spawnTime)
			{
				CircleShape shape = DrawShape(shapeVect.at(rngShape), rngRadius);
				EnemySetPosition(shape, width, height);
				EnemySetColor(shape);
				//CircleShape shape = EnemyCreate(width, height); // bug when return shape
				enemyVect.push_back(shape);
				timer.stop();
				timer.start();
			}
		#pragma endregion

		//Display
		for (unsigned i = 0; i < enemyVect.size(); i++) {
			int rngRotate = rand() % 45;
			Transform t;
			t.rotate(rng);
			window.draw(enemyVect[i], t);
		}

		Transform t2;
		t2.rotate(45);
		window.draw(rectangle, t2);
		Vector2f r1 = rectangle.getPosition();
		int r2 = rectangle.getRotation();
		rectangle.setPosition(r1 + Vector2f(0.1,0));
		rectangle.setRotation(r2 + 1);
		// Whatever I want to draw goes here
		window.display();
	}

}