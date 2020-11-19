#pragma region Lib
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <string>
#pragma endregion

#pragma region Header Files
#include "ScreenResolution.h"
#include "AssetsUtils.h"
#include "MathUtils.h"
#include "Enemy.h"
#include "PlayerController.h"
#include "Bullet.h"
#include "Collision.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Enemy.cpp"
#pragma endregion

#pragma region Namespace
using namespace std;
using namespace sf;
#pragma endregion

int main()
{
#pragma region Screen Resolution
	int width = 800;
	int height = 600;
	GetDesktopResolution(width, height);
	float halfWidth = static_cast<float>(width / 2);
	float halfHeight = static_cast<float>(height / 2);

#pragma endregion

#pragma region RNG
	srand(static_cast<unsigned int>(time(NULL)));
#pragma endregion

#pragma region Timer
	float spawnTime = 2.f;
	float deltaTime = 0.f;
	float deltaAngle = 0.f;
	Clock clockSpawn;
	Clock clockPlayer;
	Clock clockDelta;
	Clock clockInvicible;
	Time elapsedTimeSpawn;
#pragma endregion

#pragma region Player
	Player* player = new Player;
	player->triangle.setPointCount(3);
	player->triangle.setRadius(20);
	player->triangle.setPosition(halfWidth, halfHeight);
	player->triangle.setFillColor(Color::Cyan);
	player->triangle.setOrigin(20, 20);
	player->triangle.setScale(1.0f, 1.5f);
	bool defeat = false;
#pragma endregion
	////test
	//CircleShape test;
	//test.setPointCount(4);
	//test.setRadius(40);
	//test.setRotation(90);
	//test.setScale(1, .5f);
	//test.setPosition(width / 2, height / 2);
#pragma region Bullet
	bool drawBullet = false;
	Bullet* bullet = new Bullet;
#pragma endregion

#pragma region Enemy
	list<Enemy*> enemyList;
	int maxEnemy = 30;
	int countEnemy = 0;
	int countSnake = 0;
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
	
	Text gameover;
	gameover.setFont(font);
	gameover.setString("Game Over\nRestart ?\n[R]");
	gameover.setCharacterSize(150);
	gameover.setOrigin(floor(gameover.getLocalBounds().width /2), floor(gameover.getLocalBounds().height /2));
	gameover.setFillColor(Color::Red);
	gameover.setOutlineColor(Color::White);
	gameover.setOutlineThickness(.5f);
	gameover.setPosition(static_cast<float>(width / 2.0f) , static_cast<float>(height/3));
	

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
	background.setPosition(halfWidth, halfHeight);
	stars1.scale(3, 3);
	stars1.setOrigin(textureStars1.getSize().x/2 , textureStars1.getSize().y/2);
	stars1.setPosition(halfWidth, halfHeight);

	stars1.setColor(Color(255, 255, 255, 200));
#pragma endregion

#pragma region Score
	int score = 0;
	int charSizeScore = 100;
	Text scoreText;
	scoreText.setString("0");
	scoreText.setCharacterSize(charSizeScore);
	scoreText.setPosition(10.0f, static_cast<float>(-charSizeScore / 2));
	scoreText.setFont(font);
#pragma endregion
#pragma region Combo
	int comboCount = 1;
#pragma endregion
#pragma region Sound
	sf::Music music;
	music.openFromFile(getAssetsPath() + "battle.wav");
	music.setLoop(true);
	music.setVolume(0.1f);
	music.play();

	sf::SoundBuffer hit;
	hit.loadFromFile(getAssetsPath() + "hit.wav");
	sf::Sound sound;
	sound.setBuffer(hit);
	sound.setVolume(0.1f);
#pragma endregion

#pragma region Game Manager
	bool pause = false;
#pragma endregion
#pragma region TEST	
	//float snakeX = 800;
	//float snakeY = sin(snakeX);
#pragma endregion TEST

	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window"); //, Style::Fullscreen
	window.setFramerateLimit(60);

	// Game loop
	while (window.isOpen()) {
		Event event;
		//Delta Time
		deltaTime = clockDelta.getElapsedTime().asSeconds();
		clockDelta.restart();

		if (pause) {
			deltaTime = 0.0f;
		}

		//Player Movement
		Vector2f localPosition = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		Vector2f starsMove;
		if (Mouse::isButtonPressed(Mouse::Right) && (player->triangle.getPosition().x + 20 != localPosition.x || player->triangle.getPosition().y + 20 != localPosition.y) && !defeat)
		{
			starsMove = PlayerMove((*player), localPosition, deltaTime, width, height);
			//Background parallax
			stars1.move(- starsMove.x /2 , - starsMove.y /2);
			background.move(- starsMove.x /5 , - starsMove.y /5);
		}
		//Player face cursor
		if (!pause) {
			PlayerRotation((*player), localPosition);
		}

		//Player health
		if (player->invicibleTime > 0) {
			player->invicibleTime -= deltaTime;
		}

		//Fire!
		if (Mouse::isButtonPressed(Mouse::Left) && !drawBullet && !pause) {
			bullet = PlayerShot(drawBullet, localPosition, (*player), bullet);
		}

		//Collision bullet -> player : Pickup bullet
		if (drawBullet && !defeat) {
			bool hascolid = HasCollidedBullet((*bullet), player->triangle.getPosition().x, player->triangle.getPosition().y, player->triangle.getRadius());
			if (hascolid) {
				drawBullet = false;
			}
		}

		//Update bullet
		if (drawBullet && !defeat) {
			Check_Wall_Collision(bullet, width, height);
			UpdatePosition(bullet, deltaTime);
		}

		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
			}

			//PAUSE
			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::P) {
				if (!pause) {
					pause = true;
				}
				else {
					pause = false;
				}
			}

			//RESTART and reset parameters
			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				if (defeat) {
					if (!enemyList.empty()) {
						auto it = enemyList.begin();

						while (it != enemyList.end()) {
							delete (*it);
							it = enemyList.erase(it);
						}
						enemyList.clear();
					}
					countEnemy = 0;
					score = 0;
					scoreText.setString("0");
					player->life = 5;
					defeat = false;
				}
			}
		}

		//ENEMY
#pragma region Create Enemy
		elapsedTimeSpawn = clockSpawn.getElapsedTime();
		if (elapsedTimeSpawn.asSeconds() > spawnTime && countEnemy < maxEnemy && !pause)
		{
			Enemy* enemy = new Enemy(width, height);
			enemyList.push_back(enemy);
			clockSpawn.restart();
			countEnemy++;
		}
#pragma endregion
#pragma region Update Enemy
		//Move pattern
		deltaAngle = deltaTime * IIM_PI * 2.0f;
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			(*it)->update(width, height, deltaAngle, deltaTime, player);
		}

		//Collision
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			//collision Enemy -> Player 
			bool hascolidWithplayer = HasCollided((*player), (*it)->GetPosition().x, (*it)->GetPosition().y, (*it)->GetRadius());
			if (hascolidWithplayer) {
				if (player->invicibleTime <= 0) {
					if (player->life > 1) {
						player->life--;
						player->invicibleTime = 3.0f;

						(*it)->isAlive = false;
					}
					else {
						defeat = true;
						drawBullet = false;
					}
				}
			}
			//collision Enemy -> Bullet
			bool hascolidWithBullet = HasCollidedBullet((*bullet), (*it)->GetPosition().x, (*it)->GetPosition().y, (*it)->GetRadius());
			if (hascolidWithBullet && drawBullet && (*it)->GetInvicibleTime() <= 0) {
				//enemy shield
				if ((*it)->GetHasShield()) {
					(*it)->SetHasShield(false);
					(*it)->SetInvicibleTime(0.2f);
				}
				//enemy life
				else if((*it)->GetLife() > 1) {
					(*it)->UpdateLife();
					(*it)->SetInvicibleTime(0.2f);
				}
				//enemy Death
				else {
					(*it)->isAlive = false;
					//Update score
					switch ((*it)->type)
					{
					case EnemyType::BASIC:
						score += 10 * comboCount;
						break;
					case EnemyType::MINI:
						score += 100 * comboCount;
						break;
					case EnemyType::TELEPORTER:
						score += 20 * comboCount;
						break;
					case EnemyType::SNAKE:
						score += 30 * comboCount;
						break;
					case EnemyType::KAMIKAZE:
						score += 30 * comboCount;
						break;
					case EnemyType::FOLLOWER:
						score += 20 * comboCount;
						break;
					case EnemyType::DIVIDER:
						score += 30 * comboCount;
						break;
					case EnemyType::SUB:
						score += 10 * comboCount;
						break;
					case EnemyType::LIFER:
						score += 30 * comboCount;
						break;
					case EnemyType::LIFEDIVIDER:
						score += 40 * comboCount;
						break;
					default:
						score += 10 * comboCount;
						break;
					}
					scoreText.setString(to_string(score));
				}
			}
		}

		//DIVIDE ENEMY
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			if (!(*it)->isAlive) {
				//divide type
				if ((*it)->type == EnemyType::KAMIKAZE ||
					(*it)->type == EnemyType::DIVIDER ||
					(*it)->type == EnemyType::LIFEDIVIDER) 
				{
						EnemyDivide((*it), enemyList);
				}

			}
		}

		//remove invicibility
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			if ((*it)->GetInvicibleTime() > 0) {
				(*it)->UpdateInvicibleTime();
			}
		}

#pragma endregion
#pragma region Destroy ENEMY
		if (!enemyList.empty()) {
			auto it = enemyList.begin();

			while (it != enemyList.end()) {

				if (!(*it)->isAlive) {

					sound.play();
					delete (*it);
					it = enemyList.erase(it);
					countEnemy--;
				}
				else {
					it++;
				}
			}
		}
#pragma endregion

		window.clear();
		
		if (!defeat) {

			window.draw(background);
			window.draw(stars1);
			//Enemy
			for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
				window.draw((*it)->GetShape());
				if ((*it)->type == EnemyType::TELEPORTER) {
					window.draw((*it)->GetTeleportCircle());
				}
			}
			
			window.draw(player->triangle);
			if (drawBullet) {
				window.draw(bullet->visual);
			}
			window.draw(scoreText);
		}
		else {
			//Game Over
			window.draw(background);
			window.draw(gameover);
			window.draw(scoreText);
		}

		window.display();
	}

	//DESTROY end game

	while (!enemyList.empty()) {
		auto it = enemyList.begin();

		while (it != enemyList.end()) {
				delete (*it);
				it = enemyList.erase(it);
		}
		enemyList.clear();
	}

	delete player;
	delete bullet;
}