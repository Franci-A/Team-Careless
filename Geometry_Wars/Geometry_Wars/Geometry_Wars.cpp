// Geometry_Wars.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma region Lib
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#pragma endregion

#pragma region Header Files
#include "ScreenResolution.h"
#include "Enemy.h"
#include "PlayerController.h"
#include "Bullet.h"
#include "DeltaTime.h"

#pragma endregion

#pragma region Namespace
using namespace std;
using namespace sf;

#pragma endregion

#pragma region Global Variable
Timer TIMER;
//float PI = 3.141592653;

#pragma endregion

int main()
{
	#pragma region Screen Resolution
		int width = 0;
		int height = 0;
		GetDesktopResolution(width, height);
	#pragma endregion 
	#pragma region Enemy
		vector<Enemy> enemyList;
	#pragma endregion
	#pragma region Timer
		float spawnTime = 1.0f;
		float rotateTime = 1.0f;
		Clock clock;
		Clock clock2;
		Clock clockPlayer;
		Time elapsedTime;
		Time elapsedTime2;
	#pragma endregion

	#pragma region Player
		Player player;
		player.triangle.setPointCount(3);
		player.triangle.setRadius(20);
		player.triangle.setPosition(390, 290);
		player.triangle.setFillColor(sf::Color::Cyan);
		player.triangle.setOrigin(20, 20);
	#pragma endregion



	//VideoMode DesktopMode = VideoMode::GetDesktopMode();
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window", Style::Fullscreen);
	// Initialise everything below
	// Game loop
	while (window.isOpen()) {
		Event event;

		//Player Movement
		float deltaTime = clockPlayer.getElapsedTime().asSeconds();
		Vector2f localPosition = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		if (Mouse::isButtonPressed(Mouse::Right) && (player.triangle.getPosition().x + 20 != localPosition.x || player.triangle.getPosition().y + 20 != localPosition.y))
		{
			PlayerMove(player, localPosition, deltaTime);
		}
		PlayerRotation(player, localPosition);
		// 

		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
			}
		}

		window.clear();
		
		#pragma region Create Enemy
			elapsedTime = clock.getElapsedTime();
			if (elapsedTime.asSeconds() > spawnTime)
			{
				Enemy enemy;
				enemy = EnemyCreate(width, height);
				enemyList.push_back(enemy);
				//CircleShape shape = DrawShape();
				//EnemySetPosition(shape, width, height);
				//EnemySetColor(shape);
				//shape.setOrigin(shape.getRadius(), shape.getRadius());
				////CircleShape shape = EnemyCreate(width, height); // bug when return shape
				//enemySpeed.push_back(rngSpeed);
				//enemySpawnPoint.push_back(shape.getPosition());
				//enemyVect.push_back(shape);
				//enemyDirection.push_back(rngDirection);
				//enemyRotation.push_back(rngRotation);
				clock.restart();
			}
		#pragma endregion

	#pragma region Display Enemy
		elapsedTime2 = clock2.getElapsedTime();
		
		//for (unsigned i = 0; i < enemyVect.size(); i++) {	
	
		//	Vector2f r1 = enemyVect[i].getPosition();
		//	int r2 = enemyVect[i].getRotation();
		//	
		//	//UP
		//	if (enemySpawnPoint[i].x == 0) {
		//		enemyVect[i].setPosition(r1 + Vector2f(enemySpeed[i] * deltaTime, enemyDirection[i]));
		//	}
		//	//LEFT
		//	else if (enemySpawnPoint[i].y == 0) {
		//		enemyVect[i].setPosition(r1 + Vector2f(enemyDirection[i], enemySpeed[i] * deltaTime));
		//	}
		//	//RIGHT
		//	else if (enemySpawnPoint[i].x == width) {
		//		enemyVect[i].setPosition(r1 + Vector2f(-enemySpeed[i] * deltaTime, enemyDirection[i]));
		//	}
		//	//DOWN
		//	else if (enemySpawnPoint[i].y == height) {
		//		enemyVect[i].setPosition(r1 + Vector2f(enemyDirection[i], -enemySpeed[i] * deltaTime));
		//	}
		//	if (elapsedTime.asSeconds() > rotateTime) {
		//		enemyVect[i].setRotation(r2 + enemyRotation[i]);
		//		clock2.restart();
		//	}
		//	window.draw(enemyVect[i]);
		//}
	#pragma endregion
		// Whatever I want to draw goes here
		window.draw(player.triangle);
		window.display();
	}

}