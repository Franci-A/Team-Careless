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
	Clock clockInvicible;
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
	gameover.setPosition((float)width / 2.0f , (float)height/3);
	

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

#pragma region Score
	int score = 0;
	int charSizeScore = 100;
	Text scoreText;
	scoreText.setString("0");
	scoreText.setCharacterSize(charSizeScore);
	scoreText.setPosition(10, -charSizeScore / 2);
	scoreText.setFont(font);
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
			starsMove = PlayerMove((*player), localPosition, deltaTime);
			//Background parallax
			stars1.move(- starsMove.x /2 , - starsMove.y /2);
			background.move(- starsMove.x /5 , - starsMove.y /5);
		}
		//Player face cursor
		if (!pause) {
			PlayerRotation((*player), localPosition);
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
			Enemy* enemi = new Enemy;
			enemi = EnemyCreate(width, height);

			//SNAKE ID
			//if (enemi->type == EnemyType::SNAKE) {
			//	countSnake++;
			//	enemi->snakeID = countSnake;
			//}
			enemyList.push_back(enemi);

			////SNAKE TAIL CREATION
			//if (enemi->type == EnemyType::SNAKE) {
			//	for (int i = 0; i < enemi->snakeLength; i++) {
			//		Enemy* tail = new Enemy;
			//		tail = EnemySnakeTail(*enemyList.rbegin());
			//		tail->snakeID = countSnake;
			//		enemyList.push_back(tail);
			//	}
			//}

			clockSpawn.restart();
			countEnemy++;
		}
#pragma endregion
#pragma region Update Enemy
		//MOVE & COLLISION & ALIVE & SCORE
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			deltaAngle = deltaTime * IIM_PI * 2.0f * (*it)->rotation;
			EnemyUpdate(*it, width, height, deltaTime, deltaAngle, player, enemyList);
			
			//draw circle of teleportation
			if((*it)->type == EnemyType::TELEPORTER && (*it)->teleportPosition != Vector2f(-1.0f, -1.0f)) {
				(*it)->teleportCircle.setRadius((*it)->radius);
				(*it)->teleportCircle.setFillColor(Color(0, 0, 150, 150));
				(*it)->teleportCircle.setOrigin((*it)->teleportCircle.getRadius(), (*it)->teleportCircle.getRadius());
				(*it)->teleportCircle.setPosition((*it)->teleportPosition);
			}

			//collision Player -> enemy
			bool hascolidWithplayer = HasCollided((*player), (*it)->shape.getPosition().x, (*it)->shape.getPosition().y, (*it)->radius);
			if (hascolidWithplayer) {
				if (player->invicibleTime <= 0) {
					if (player->life > 1) {
						player->life--;
						player->invicibleTime = 3.0f;
					}
					else {
						defeat = true;
						drawBullet = false;
					}
				}
			}

			//When divide enemy sub don't get destroy immediatly
			if (player->invicibleTime > 0) {
				player->invicibleTime -= deltaTime;
			}
			//collision bullet -> enemy
			bool hascolidWithBullet = HasCollidedBullet((*bullet), (*it)->shape.getPosition().x, (*it)->shape.getPosition().y, (*it)->radius);
			if (hascolidWithBullet && drawBullet && (*it)->invicibleTime <= 0) {
				//enemy shield
				if ((*it)->hasOutline) {
					(*it)->shape.setOutlineThickness(0);
					(*it)->hasOutline = false;
					(*it)->invicibleTime = 0.2f;
				}
				//enemy life
				else if((*it)->life > 1) {
					(*it)->life--;
					(*it)->shape.setRadius((*it)->radius / 1.5f);
					(*it)->radius = (*it)->shape.getRadius();
					(*it)->shape.setOrigin((*it)->radius, (*it)->radius);
					(*it)->shape.setFillColor(Color((*it)->shape.getFillColor().r, (*it)->shape.getFillColor().g *2 ,0));
					(*it)->invicibleTime = 0.2f;
				}
				//Dead
				//TAil of snake can't be destroy until head is dead
				else if((*it)->type != EnemyType::TAIL) {
					(*it)->isAlive = false;
					//Update score
					score += (*it)->scoreValue;
					scoreText.setString(to_string(score));
				}
			}
		}

		//DIVIDE ENEMY
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			if (!(*it)->isAlive) {
				//divide type
				if ((*it)->canDivide) {
					EnemyDivide((*it), enemyList, width, height);
				}
			}
		}

		//remove invicible of divide and outline type
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			if ((*it)->invicibleTime > 0) {
				(*it)->invicibleTime -= deltaTime;
			}
		}

#pragma endregion

		//BUG CRASH HERE
#pragma region Destroy ENEMY
		int tempID = 0; //for deleting corresponding tail of snake
		if (!enemyList.empty()) {
			auto it = enemyList.begin();

			while (it != enemyList.end()) {

				if (!(*it)->isAlive) {

					//get the snake head id to delete corresponding tail
					//if ((*it)->type == EnemyType::SNAKE) {
					//	tempID = (*it)->snakeID;
					//}
					
					sound.play();
					delete (*it);
					it = enemyList.erase(it);
					
					//delete tail of snake
					//while ((*it)->type == EnemyType::TAIL && (*it)->snakeID == tempID) {
					//	delete (*it);
					//	it = enemyList.erase(it);
					//}
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
				window.draw((*it)->shape);
				if ((*it)->type == EnemyType::TELEPORTER && (*it)->timeBeforeTeleport <= 0) {
					window.draw((*it)->teleportCircle);
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