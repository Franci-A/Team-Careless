// Geometry_Wars.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma region Lib
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#pragma endregion

#pragma region Header Files
#include "ScreenResolution.h"
#include "AssetsUtils.h"
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
	float spawnTime = 1.f;
	float rotateTime = 1.f;
	float deltaTime = 0.f;
	Clock clockSpawn;
	Clock clock2;
	Clock clockPlayer;
	Clock clockDelta;
	Time elapsedTime;
	Time elapsedTime2;
#pragma endregion
#pragma region Player
	Player player;
	player.triangle.setPointCount(3);
	player.triangle.setRadius(20);
	player.triangle.setPosition((float)width / 2, (float)height / 2);
	player.triangle.setFillColor(Color::Cyan);
	player.triangle.setOrigin(20, 20);
	player.triangle.setScale(1.0f, 1.5f);
	bool defeat = false;
#pragma endregion
#pragma region Enemy
	vector<Enemy*> enemyVect;
	int maxEnemy = 30;
	int countEnemy = 0;
	Transform t;
#pragma endregion
#pragma region Bullet
	bool drawBullet = false;
	Bullet* bullet = new Bullet;
#pragma endregion

#pragma region CANVAS
	Text gameover;
	gameover.setString("Game Over");
	gameover.setCharacterSize(50);
	gameover.setFillColor(Color::Red);
	float offsetX = gameover.getCharacterSize() * 8 / 2;
	gameover.setPosition((float)width / 2.0f - offsetX, (float)height / 2.0f);
	Font font;
	if (!font.loadFromFile(getAssetsPath() + "arial.ttf"))
	{
		cout << "Error Load font" << endl;
		cout << "AppPATH " << endl << getAppPath << endl;
		cout << "AssetPATH " << endl << getAssetsPath() << endl;
	}
	gameover.setFont(font);
#pragma endregion

#pragma region TEST CREATE AT START ENEMY

	//CREATE AT START
	//for (int i = 0; i < maxEnemy; i++) {
	//	Enemy* enemi = new Enemy;
	//	enemi = EnemyCreate(width, height);
	//	enemyVect.push_back(enemi);
	//}

#pragma endregion

	//VideoMode DesktopMode = VideoMode::GetDesktopMode();
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window"); //Style::Fullscreen
	window.setFramerateLimit(60);
	// Initialise everything below
	// Game loop
	while (window.isOpen()) {
		Event event;
		//Delta Time
		deltaTime = clockPlayer.getElapsedTime().asSeconds();

		//Player Movement
		Vector2f localPosition = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		if (Mouse::isButtonPressed(Mouse::Right) && (player->triangle.getPosition().x + 20 != localPosition.x || player->triangle.getPosition().y + 20 != localPosition.y))
		{
			PlayerMove((*player), localPosition, deltaTime);
		}
		PlayerRotation((*player), localPosition);

		if (Mouse::isButtonPressed(Mouse::Left) && !drawBullet) {
			//cout << localPosition.x <<  " " << localPosition.y << endl;
			//cout << player.triangle.getPosition().x << " " << player.triangle.getPosition().y << endl;
			bullet = PlayerShot(drawBullet, localPosition, player, bullet);
			//cout << bullet->X_offset << " " << bullet->Y_offset << endl;
		}
		if (drawBullet) {
			bool hascolid = HasCollidedBullet((*bullet), player->triangle.getPosition().x, player->triangle.getPosition().y, player->triangle.getRadius());
				if (hascolid) {
					drawBullet = false;
				}
		}

		if (drawBullet) {
			Check_Wall_Collision(bullet, width, height);
			UpdatePosition(bullet);
		}

		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				delete player;
				delete bullet;
				window.close();
			}
		}

		//ENEMY
#pragma region Create Enemy
		elapsedTime = clockSpawn.getElapsedTime();
		if (elapsedTime.asSeconds() > spawnTime && countEnemy < maxEnemy)
		{
			Enemy* enemi = new Enemy;
			enemi = EnemyCreate(width, height);
			enemyVect.push_back(enemi);

			clockSpawn.restart();
			countEnemy++;
		}
#pragma endregion
#pragma region Update Enemy
		for (auto it = enemyVect.begin(); it != enemyVect.end(); it++) {
			EnemyUpdate(*it, width, height);
			
			//Direction Enemy
			t.rotate((*it)->angle, (*it)->spawnPoint.x, (*it)->spawnPoint.y);
			
			if (!(*it)->hasSpawn) {
				(*it)->shape.setPosition((*it)->spawnPoint);
			}

			//collision 
			bool hascolidWithplayer = HasCollided(player, (*it)->shape.getPosition().x, (*it)->shape.getPosition().y, (*it)->radius);
			if (hascolidWithplayer) {
				//Defaite----------------------
				defeat = true;
			}
			bool hascolidWithBullet = HasCollidedBullet((*bullet), (*it)->shape.getPosition().x, (*it)->shape.getPosition().y, (*it)->radius);
			if (hascolidWithBullet && drawBullet) {
				//destroy ennemis---------------
				(*it)->isAlive = false;
			}
		}
#pragma endregion
#pragma region DESTROY ENEMY
		//NEED LONG TEST
		if(!enemyVect.empty()){
			auto it = enemyVect.begin();

			while (it != enemyVect.end()) {

				if (!(*it)->isAlive) {
					delete (*it);
					it = enemyVect.erase(it);
				}
				it++;
			}
		}
#pragma endregion

		window.clear();

		if (!defeat) {
			// Whatever I want to draw goes here
			//Enemy
			for (auto it = enemyVect.begin(); it != enemyVect.end(); it++) {
				if (!(*it)->hasSpawn) {
					window.draw((*it)->shape, t);
					(*it)->hasSpawn = true;
				}
				window.draw((*it)->shape);
			}
			// Whatever I want to draw goes here
			window.draw(player->triangle);
			if (drawBullet) {
				window.draw(bullet->visual);
			}
		}
		else {
			//Game Over
			window.draw(gameover);
		}

		window.display();
	}

	//DESTROY

	int count = 1;
	while (!enemyVect.empty()) {
		cout << "delete " << count << endl;
		delete enemyVect.at(0);
		enemyVect.erase(enemyVect.begin());
		count++;
		
	}
	delete bullet;
}