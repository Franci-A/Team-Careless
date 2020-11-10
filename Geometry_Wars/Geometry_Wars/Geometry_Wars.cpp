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

using namespace std;
using namespace sf;

int main()
{
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
		vector<Vector2f> enemySpawnPoint;
		vector<float> enemySpeed;
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
		int rngSpeedLimit = rand() % 10 + 1;
		float rngSpeed = (float)rngSpeedLimit / 10;
	#pragma endregion 
	#pragma region Timer
		float spawnTime = 1.0f;
		float rotateTime = 1.0f;
		Clock clock;
		Clock clock2;
		Time elapsedTime;
		Time elapsedTime2;
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
			rngSpeedLimit = rand() % 10 + 1;
			rngSpeed = (float)rngSpeedLimit / 20;
		#pragma endregion 

		#pragma region Spawn Enemy
			elapsedTime = clock.getElapsedTime();
			if (elapsedTime.asSeconds() > spawnTime)
			{
				CircleShape shape = DrawShape(shapeVect.at(rngShape), rngRadius);
				EnemySetPosition(shape, width, height);
				EnemySetColor(shape);
				shape.setOrigin(shape.getRadius(), shape.getRadius());
				//CircleShape shape = EnemyCreate(width, height); // bug when return shape
				enemySpeed.push_back(rngSpeed);
				enemySpawnPoint.push_back(shape.getPosition());
				enemyVect.push_back(shape);
				clock.restart();
			}
		#pragma endregion

	#pragma region Display Enemy
		elapsedTime2 = clock2.getElapsedTime();
		for (unsigned i = 0; i < enemyVect.size(); i++) {
			
			

			Vector2f r1 = enemyVect[i].getPosition();
			int r2 = enemyVect[i].getRotation();
			
			if (enemySpawnPoint[i].x == 0) {
				enemyVect[i].setPosition(r1 + Vector2f(enemySpeed[i], 0));
			}
			else if (enemySpawnPoint[i].y == 0) {
				enemyVect[i].setPosition(r1 + Vector2f(0, enemySpeed[i]));
			}
			else if (enemySpawnPoint[i].x == width) {
				enemyVect[i].setPosition(r1 + Vector2f(-enemySpeed[i], 0));
			}
			else if (enemySpawnPoint[i].y == height) {
				enemyVect[i].setPosition(r1 + Vector2f(0, -enemySpeed[i]));
			}
			if (elapsedTime.asSeconds() > rotateTime) {
				enemyVect[i].setRotation(r2 + 30);
				clock2.restart();
			}

			window.draw(enemyVect[i]);
		}
	#pragma endregion
		// Whatever I want to draw goes here
		window.display();
	}

}