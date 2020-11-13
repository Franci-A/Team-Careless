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
#include "MathUtils.h"
#include "Enemy.h"
#include "PlayerController.h"
#include "Bullet.h"
#include "DeltaTime.h"
#include "Collision.h"
#include "Score.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

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
	int width = 800;
	int height = 600;
	GetDesktopResolution(width, height);
#pragma endregion
#pragma region RNG
	srand(time(NULL));
#pragma endregion
#pragma region Timer
	float spawnTime = 1.f;
	float deltaTime = 0.f;
	float deltaAngle = 0.f;
	Clock clockSpawn;
	Clock clockPlayer;
	Clock clockDelta;
	Time elapsedTimeSpawn;
#pragma endregion
#pragma region Player
	Player* player = new Player;
	player->triangle.setPointCount(3);
	player->triangle.setRadius(20);
	player->triangle.setPosition((float)width / 2, (float)height / 2);
	player->triangle.setFillColor(Color::Cyan);
	player->triangle.setOrigin(20, 20);
	player->triangle.setScale(1.0f, 1.5f);
	bool defeat = false;
#pragma endregion
#pragma region Bullet
	bool drawBullet = false;
	Bullet* bullet = new Bullet;
#pragma endregion
#pragma region Enemy
	vector<Enemy*> enemyVect;
	int maxEnemy = 30;
	int countEnemy = 0;
#pragma endregion


#pragma region CANVAS
	Font font;
	string fontPath = getAssetsPath() + "mago2.ttf";
	if (!font.loadFromFile(fontPath))
	{
		std::cout << "Error Load font" << endl;
		std::cout << "AppPATH " << endl << getAppPath << endl;
		std::cout << "AssetPATH " << endl << getAssetsPath() << endl;
	}


#pragma region Score
	int score = 0;
	int charSizeScore = 100;
	Text scoreText;
	scoreText.setString("0");
	scoreText.setCharacterSize(charSizeScore);
	scoreText.setPosition(10, -charSizeScore/2);
	scoreText.setFont(font);
#pragma endregion
#pragma region GameOver
	Text gameover;
	int charSizeGO = 100;
	gameover.setString("Game Over");
	gameover.setCharacterSize(charSizeGO);
	//gameover.setOrigin(150, 100);
	gameover.setFillColor(Color::Red);
	//float offsetX = gameover.getCharacterSize() * 8 / 2;
	//gameover.setPosition((float)width / 2.0f /*- offsetX*/, (float)height / 2.0f);
	gameover.setPosition(width/2 - charSizeGO * 2, height/2 - charSizeGO); //-charSizeGo/2 get it to approxi height
	gameover.setFont(font);
#pragma endregion
#pragma region Sprite
	Texture texture;
	Texture textureStars1;
	if (!texture.loadFromFile(getAssetsPath() + "bg_space_seamless.png")) {
		std::cout << "Error load space " << endl;
	}
	if (!textureStars1.loadFromFile(getAssetsPath() + "bg_space_seamless_fl1.png")) {
		std::cout << "Error load stars 1 " << endl;
	}
	Sprite background;
	Sprite stars1;

	background.setTexture(texture);
	stars1.setTexture(textureStars1);

	background.scale(3, 3);
	background.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
	background.setPosition(width/2, height/2);
	stars1.scale(3, 3);
	stars1.setOrigin(textureStars1.getSize().x/2 , textureStars1.getSize().y/2);
	stars1.setPosition(width/2, height/2 );

	stars1.setColor(Color(255, 255, 255, 200));
#pragma endregion
#pragma endregion
#pragma region Sound
	sf::Music music;
	music.openFromFile(getAssetsPath() + "battle.wav");
	music.setLoop(true);
	music.setVolume(1);
	music.play();

	sf::SoundBuffer hit;
	hit.loadFromFile(getAssetsPath() + "hit.wav");
	sf::Sound sound;
	sound.setBuffer(hit);
	sound.setVolume(1);

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
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window", Style::Fullscreen); //Style::Fullscreen
	window.setFramerateLimit(60);
	// Initialise everything below
	// Game loop
	while (window.isOpen()) {
		Event event;
		//Delta Time
		deltaTime = clockDelta.getElapsedTime().asSeconds();
		clockDelta.restart();
		//Player Movement
		Vector2f localPosition = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		Vector2f starsMove;
		if (Mouse::isButtonPressed(Mouse::Right) && (player->triangle.getPosition().x + 20 != localPosition.x || player->triangle.getPosition().y + 20 != localPosition.y))
		{
			starsMove = PlayerMove((*player), localPosition, deltaTime);
			stars1.move(- starsMove.x /2 , - starsMove.y /2);
			background.move(- starsMove.x /5 , - starsMove.y /5);
		}

		PlayerRotation((*player), localPosition);

		if (Mouse::isButtonPressed(Mouse::Left) && !drawBullet) {
			//cout << localPosition.x <<  " " << localPosition.y << endl;
			//cout << player.triangle.getPosition().x << " " << player.triangle.getPosition().y << endl;
			bullet = PlayerShot(drawBullet, localPosition, (*player), bullet);
			//cout << bullet->X_offset << " " << bullet->Y_offset << endl;
		}
		if (drawBullet && !defeat) {
			bool hascolid = HasCollidedBullet((*bullet), player->triangle.getPosition().x, player->triangle.getPosition().y, player->triangle.getRadius());
			if (hascolid) {
				drawBullet = false;
			}
		}

		if (drawBullet && !defeat) {
			Check_Wall_Collision(bullet, width, height);
			UpdatePosition(bullet, deltaTime);
		}

		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
			}
		}

		//ENEMY
#pragma region Create Enemy
		elapsedTimeSpawn = clockSpawn.getElapsedTime();
		if (elapsedTimeSpawn.asSeconds() > spawnTime && countEnemy < maxEnemy)
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
			deltaAngle = deltaTime * IIM_PI * 2.0f * (*it)->rotation;
			EnemyUpdate(*it, width, height, deltaTime, deltaAngle);

			//collision 
			bool hascolidWithplayer = HasCollided((*player), (*it)->shape.getPosition().x, (*it)->shape.getPosition().y, (*it)->radius);
			if (hascolidWithplayer) {
				//Defaite----------------------
				defeat = true;
			}
			bool hascolidWithBullet = HasCollidedBullet((*bullet), (*it)->shape.getPosition().x, (*it)->shape.getPosition().y, (*it)->radius);
			if (hascolidWithBullet && drawBullet) {
				//destroy ennemis---------------
				(*it)->isAlive = false;
				//Update score
				score += (*it)->scoreValue;
				scoreText.setString(to_string(score));
			}
		}
#pragma endregion
#pragma region Destroy ENEMY
		
		if (!enemyVect.empty()) {
			auto it = enemyVect.begin();

			while (it != enemyVect.end()) {

				if (!(*it)->isAlive) {
					sound.play();
					delete (*it);
					it = enemyVect.erase(it);
					countEnemy--;
				}
				else {
					it++;
				}
			}
		}
#pragma endregion

#pragma region Update Canvas
#pragma endregion

		window.clear();

		if (!defeat) {
			// Whatever I want to draw goes here
			window.draw(background);
			window.draw(stars1);
			
			//Enemy
			for (auto it = enemyVect.begin(); it != enemyVect.end(); it++) {
					window.draw((*it)->shape);
			}
			// Whatever I want to draw goes here
			window.draw(player->triangle);
			if (drawBullet) {
				window.draw(bullet->visual);
			}
			window.draw(scoreText);
		}
		else {
			//Game Over
			window.draw(gameover);
			window.draw(scoreText);
		}

		window.display();
	}

	//DESTROY

	int count = 1;
	while (!enemyVect.empty()) {
		std::cout << "delete " << count << endl;
		delete enemyVect.at(0);
		enemyVect.erase(enemyVect.begin());
		count++;

	}

	delete player;
	std::cout << "player delete" << endl;
	delete bullet;
	std::cout << "bullet delete" << endl;
}