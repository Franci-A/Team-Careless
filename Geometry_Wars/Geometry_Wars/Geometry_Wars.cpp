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
	#pragma region RNG
		srand(time(NULL));
	#pragma endregion
	#pragma region Timer
		float spawnTime = 0.1f;
		float rotateTime = 1.0f;
		Clock clock3;
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
		player.triangle.setFillColor(Color::Cyan);
		player.triangle.setOrigin(20, 20);
	#pragma endregion
	#pragma region Enemy
		vector<Enemy> enemyList;
		vector<CircleShape> enemyShapeList;
	#pragma endregion

	//VideoMode DesktopMode = VideoMode::GetDesktopMode();
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window"); //Style::Fullscreen
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

		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
			}
		}

		window.clear();
		
		#pragma region Create Enemy
			elapsedTime = clock3.getElapsedTime();
			if (elapsedTime.asSeconds() > spawnTime)
			{
				Enemy enemy = EnemyCreate(width, height);
				CircleShape shape = CreateEnemyShape(enemy);
				enemyList.push_back(enemy);
				enemyShapeList.push_back(shape);
				clock3.restart();
			}
		#pragma endregion
		#pragma region Update Enemy
		elapsedTime2 = clock2.getElapsedTime();
		for (unsigned u = 0; u < enemyShapeList.size(); u++) {
			if (enemyList.at(u).hasSpawn) {
				enemyShapeList.at(u).setPosition(enemyShapeList.at(u).getPosition() + enemyList.at(u).velocity);
			}
		}
		#pragma endregion

		// Whatever I want to draw goes here
		#pragma region Display Enemy
		for (unsigned u = 0; u < enemyShapeList.size(); u++) {
			Transform t;
			t.rotate(enemyList.at(u).angle);
			
			//cout << enemyList.at(u).angle << endl;
			window.draw(enemyShapeList.at(u), t);

			if (!enemyList.at(u).hasSpawn) {
				enemyList.at(u).hasSpawn = true;
			}
		}
		//if rotate transform, axis rotate too
		#pragma endregion
		window.draw(player.triangle);
		window.display();
	}

}