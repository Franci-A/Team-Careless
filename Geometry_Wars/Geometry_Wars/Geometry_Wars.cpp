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
#include "Collision.h"

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
		float spawnTime = 1.0f;
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
		player.triangle.setPosition(width/2, height/2);
		player.triangle.setFillColor(Color::Cyan);
		player.triangle.setOrigin(20, 20);
		player.triangle.setScale(1.0f, 1.5f);
		bool defeat = false;
		sf::Text gameover;
		gameover.setString("Game Over");
		gameover.setCharacterSize(50);
		gameover.setFillColor(sf::Color::Red);
		gameover.setPosition(width / 2, height / 2);

	#pragma endregion
	#pragma region Enemy
		vector<Enemy> enemyList;
		vector<CircleShape> enemyShapeList;
		int maxEnemy = 30;
		int countEnemy = 0;
		Transform t;
	#pragma endregion
	#pragma region Bullet
		bool drawBullet = false;
		Bullet* bullet = new Bullet;
	#pragma endregion
	
	#pragma region TEST
		//for (auto it = myvector.begin(); it != myvector.end(); ++it) 
		//cout << ' ' << *it;
		vector<Enemy*> enemyVect;
		Enemy* enemi = new Enemy;
		enemyVect.push_back(enemi);
		cout << "enemi isAlive = " << enemi->isAlive << endl;
		cout << "enemyVect isAlive = " << enemyVect.at(0)->isAlive << endl;
		delete enemyVect.at(0);
		enemyVect.erase(enemyVect.begin() + 0);
		cout << "enemyVect delete" << endl;
		if (!enemyVect.empty()) {
			cout << "enemi isAlive = " << enemi->isAlive << endl;
			cout << "enemyVect isAlive = " << enemyVect.at(0)->isAlive << endl;
		}
		//it = pointer to the element inside the container

		//CREATE
		for (int i = 0; i < maxEnemy; i++) {
			Enemy* enemi = new Enemy;
			enemi = EnemyDCreate(width, height);
			enemyVect.push_back(enemi);
		}

		//DRAW
		for (auto it = enemyVect.begin(); it != enemyVect.end(); it++) {
			cout << (*it)->shape.getRadius() << endl;
		}

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

		if (Mouse::isButtonPressed(Mouse::Left) && !drawBullet) {
			//cout << localPosition.x <<  " " << localPosition.y << endl;
			//cout << player.triangle.getPosition().x << " " << player.triangle.getPosition().y << endl;
			bullet = PlayerShot(drawBullet, localPosition, player, bullet);
			//cout << bullet->X_offset << " " << bullet->Y_offset << endl;
		}
		//if (drawBullet) {
		//	bool hascolid = HasCollidedBullet((*bullet), player.triangle.getPosition().x, player.triangle.getPosition().y, player.triangle.getRadius());
		//		if (hascolid) {
		//			drawBullet = false;
		//		}
		//}

		if (drawBullet) {
			Check_Wall_Collision(bullet, width, height);
			UpdatePosition(bullet);
		}

		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
			}
		}
		#pragma region Create Enemy
		elapsedTime = clock3.getElapsedTime();
		if (elapsedTime.asSeconds() > spawnTime && countEnemy < maxEnemy)
		{
			Enemy enemy = EnemyCreate(width, height);
			CircleShape shape = CreateEnemyShape(enemy);
			enemyList.push_back(enemy);
			enemyShapeList.push_back(shape);
			clock3.restart();
			countEnemy++;
		}
		#pragma endregion
		#pragma region Update Enemy
		for (unsigned u = 0; u < enemyShapeList.size(); u++) {
			//if (enemyList.at(u).hasSpawn) {
				enemyShapeList.at(u).setPosition(enemyShapeList.at(u).getPosition().x + enemyList.at(u).velocity.x, enemyShapeList.at(u).getPosition().y + enemyList.at(u).velocity.y);

				if (enemyShapeList.at(u).getPosition().x > width)	enemyShapeList.at(u).setPosition(0, enemyShapeList.at(u).getPosition().y);
				if (enemyShapeList.at(u).getPosition().x < 0) enemyShapeList.at(u).setPosition(width, enemyShapeList.at(u).getPosition().y);
				if (enemyShapeList.at(u).getPosition().y > height)	enemyShapeList.at(u).setPosition(enemyShapeList.at(u).getPosition().x, 0);
				if (enemyShapeList.at(u).getPosition().y < 0) enemyShapeList.at(u).setPosition(enemyShapeList.at(u).getPosition().x, height);

				bool hascolidWithplayer = HasCollided(player, enemyShapeList.at(u).getPosition().x , enemyShapeList.at(u).getPosition().y, enemyShapeList.at(u).getRadius());
				if (hascolidWithplayer) {
					//Defaite----------------------
					defeat = true;
				}
				bool hascolidWithBullet = HasCollidedBullet((*bullet), enemyShapeList.at(u).getPosition().x, enemyShapeList.at(u).getPosition().y, enemyShapeList.at(u).getRadius());
				if (hascolidWithBullet && drawBullet) {
					//destroy ennemis---------------
					enemyList.at(u).isAlive = false;
				}
			//}
		}

		//Destroy Enemy (and immediatly create one just after)
		if(!enemyList.empty()){
			unsigned tempCount = enemyList.size();
			unsigned u = 0;
			while(u < tempCount){
				if (!enemyList.at(u).isAlive) {
					enemyList.erase(enemyList.begin() + u);
					enemyShapeList.erase(enemyShapeList.begin() + u);

					//Create new Enemy
					//Enemy enemy = EnemyCreate(width, height);
					//CircleShape shape = CreateEnemyShape(enemy);
					//enemyList.push_back(enemy);
					//enemyShapeList.push_back(shape);
					u--;
					tempCount--;
				}
				u++;
			}
		}


		//Direction of enemy
		//for (unsigned u = 0; u < enemyShapeList.size(); u++) {
		//	t.rotate(enemyList.at(u).angle, enemyList.at(u).spawnPoint.x, enemyList.at(u).spawnPoint.y);

		//	if (!enemyList.at(u).hasSpawn) {
		//		enemyShapeList.at(u).setPosition(enemyList.at(u).spawnPoint);
		//		enemyList.at(u).hasSpawn = true;
		//	}
			

		//}
		#pragma endregion



		window.clear();
		for (auto it = enemyVect.begin(); it != enemyVect.end(); it++) {
			(*it)->shape.setFillColor((*it)->color);
			(*it)->shape.setPosition((*it)->spawnPoint);
			window.draw((*it)->shape);
		}
		if (!defeat) {
			for (unsigned u = 0; u < enemyShapeList.size(); u++) {
				window.draw(enemyShapeList.at(u), t);
			}
			// Whatever I want to draw goes here
			window.draw(player.triangle);
			if (drawBullet) {
				window.draw(bullet->visual);
			}
		}
		else {
			window.draw(gameover);
		}
		window.display();
	}

	//DESTROY
	while (!enemyVect.empty()) {
		cout << "enemyVect isAlive = " << enemyVect.at(0)->isAlive << endl;
		delete enemyVect.at(0);
		enemyVect.erase(enemyVect.begin());
	}

	delete bullet;
}