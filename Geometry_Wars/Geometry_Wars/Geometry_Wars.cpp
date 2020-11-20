#pragma region Lib
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#pragma endregion

#pragma region Header Files
#include "ScreenResolution.h"
#include "AssetsUtils.h"
#include "MathUtils.h"
#include "Enemy.h"
#include "EnemyClass.h"
#include "PlayerController.h"
#include "Bullet.h"
#include "Collision.h"
#include "Bonus.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#pragma endregion

#pragma region Namespace
using namespace std;
using namespace sf;
#pragma endregion

void RainbowEffect(int& r, bool& addR);
void BombExpandEffect(float& s, bool& addS);
void BombExplodEffect(float& s, Bonus* bonus);

int main()
{
#pragma region Screen Resolution
	int width = 800;
	int height = 600;
	GetDesktopResolution(width, height);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
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
	Clock clockBonus;
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
	////test
	//CircleShape test;
	//test.setPointCount(4);
	//test.setRadius(40);
	//test.setRotation(90);
	//test.setScale(1, .5f);
	//test.setPosition(width / 2, height / 2);
#pragma region Bullet
	bool drawBullet = false;
	//Bullet* bullet = new Bullet; // � remplacer par ~~ player->bulletList.bullet
	// Tests Powerups
	map<BALL_TYPE, Bullet_Powerup> bulletpedia;
	InitializeBulletpedia(bulletpedia);

	PowerupSwap(player, BALL_TYPE::SNAKE, bulletpedia);
#pragma endregion

	Bonus* bonus = new Bonus;
	bool drawBonus = false;
	bool speedBonus = false;
	bool invicibleBonus = false;
	bool drawBomb = false;
	bool canPlaceBomb = false;
	bool bombExploding = false;
	int r = 0;
	bool addR = true;
	int g = 128;
	bool addG = true;
	int b = 255;
	bool addB = false;
	float s = 1.2f;
	bool addS = true;

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
	gameover.setOrigin(floor(gameover.getLocalBounds().width / 2), floor(gameover.getLocalBounds().height / 2));
	gameover.setFillColor(Color::Red);
	gameover.setOutlineColor(Color::White);
	gameover.setOutlineThickness(.5f);
	gameover.setPosition((float)width / 2.0f, (float)height / 3);


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
	background.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	background.setPosition(width / 2, height / 2);
	stars1.scale(3, 3);
	stars1.setOrigin(textureStars1.getSize().x / 2, textureStars1.getSize().y / 2);
	stars1.setPosition(width / 2, height / 2);

	stars1.setColor(Color(255, 255, 255, 200));
#pragma endregion

#pragma region Score
	int score = 0;
	int comboCount = 1;
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

	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window", sf::Style::Default, settings); //, Style::Fullscreen
	window.setFramerateLimit(60);

	// Game loop
	while (window.isOpen()) {
		Event event;
		//Delta Time
		deltaTime = clockDelta.getElapsedTime().asSeconds();
		clockDelta.restart();

		if (!drawBonus && clockBonus.getElapsedTime().asSeconds() - bonus->timer > 10.0f) {
			SpawnBonus(bonus, width, height, drawBonus);
		}
		else if (drawBonus && bonus->bonustype == BonusType::INVINCIBIL) {
			RainbowEffect(r, addR);
			RainbowEffect(g, addG);
			RainbowEffect(b, addB);
			bonus->shape.setFillColor(sf::Color::Color(r, g, b));
		}

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
			stars1.move(-starsMove.x / 2, -starsMove.y / 2);
			background.move(-starsMove.x / 5, -starsMove.y / 5);
		}
		//Player face cursor
		if (!pause) {
			PlayerRotation((*player), localPosition);
		}

		//Fire!
		if (Mouse::isButtonPressed(Mouse::Left) && canPlaceBomb) {
			canPlaceBomb = false;
			PlaceBomb(player->triangle.getPosition(), bonus, drawBomb, player);
		}
		else if (Mouse::isButtonPressed(Mouse::Left) && !drawBullet && !pause) {
			PlayerShot(drawBullet, localPosition, (*player));
		}

		//Collision bullet -> player : Pickup bullet
		if (drawBullet && !defeat) {
			for (auto it = player->bulletList.begin(); it != player->bulletList.end(); it++) {
				bool hascolid = HasCollidedBullet((*(*it)), player->triangle.getPosition().x, player->triangle.getPosition().y, player->triangle.getRadius());
				if (hascolid) {
					drawBullet = false;

					if ((*it)->type == BALL_TYPE::TRIPLE) {
						(*it)->X_offset = 0;
						(*it)->Y_offset = 0;
					}
					else if ((*it)->type == BALL_TYPE::ACCELERATOR) {
						(*it)->speed = bulletpedia[BALL_TYPE::ACCELERATOR].speed;
					}
				}
			}
		}

		//Collision player -> bonus
		if (drawBonus && HasCollided((*player), bonus->shape.getPosition().x, bonus->shape.getPosition().y, 20.0f)) {
			drawBonus = false;
			BonusCollected(bonus, player, clockBonus.getElapsedTime().asSeconds());
			if (bonus->bonustype == BonusType::SPEED) {
				speedBonus = true;
			}
			else if (bonus->bonustype == BonusType::INVINCIBIL) {
				invicibleBonus = true;
			}
			else if (bonus->bonustype == BonusType::BOMB) {
				canPlaceBomb = true;
			}
		}

		if (speedBonus && clockBonus.getElapsedTime().asSeconds() - bonus->bonusTimer > 10.0f) {
			speedBonus = false;
			player->speed -= 300;
			player->triangle.setOutlineThickness(0);
		}
		else if (invicibleBonus && clockBonus.getElapsedTime().asSeconds() - bonus->bonusTimer > 5.0f) {
			invicibleBonus = false;
			player->triangle.setFillColor(sf::Color::Cyan);
			player->speed -= 200;
		}
		else if (invicibleBonus) {
			RainbowEffect(r, addR);
			RainbowEffect(g, addG);
			RainbowEffect(b, addB);
			player->triangle.setFillColor(sf::Color::Color(r, g, b));
		}
		else if (bombExploding && clockBonus.getElapsedTime().asSeconds() - bonus->bonusTimer > 3.5f) {
			bombExploding = false;
			drawBomb = false;
			s = 1.2;
		}
		else if (drawBomb && clockBonus.getElapsedTime().asSeconds() - bonus->bonusTimer > 3.0f) {
			bombExploding = true;
		}
		
		if (bombExploding) {
			BombExplodEffect(s, bonus);
			
		}
		else if (drawBomb) {
			BombExpandEffect(s, addS);
			bonus->bombShape.setScale(s, s);
		}

		if (canPlaceBomb) {
			bonus->timer = clockBonus.getElapsedTime().asSeconds();
		}
		//Update bullet
		if (drawBullet && !defeat) {
			for (auto it = player->bulletList.begin(); it != player->bulletList.end(); it++) {
				Check_Wall_Collision((*it), width, height);
				UpdatePosition((*it), deltaTime);
			}
			//Check_Wall_Collision(bullet, width, height);
			//UpdatePosition(bullet, deltaTime);
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
					if (player->life > 1 && !player->hasShield) {
						player->life--;
						player->invicibleTime = 3.0f;

						(*it)->isAlive = false;
					}
					else if (player->hasShield) {
						(*it)->isAlive = false;
						player->triangle.setOutlineThickness(0);
						player->hasShield = false;
					}
					else {
						defeat = true;
						drawBullet = false;
					}
				}
			}
			//collision Enemy -> Bullet + bomb bonus
			list<Bullet*>::iterator bullet_it = player->bulletList.begin();
			bool hascolidWithBullet = false;
			bool hasColidWithBomb = false;
			while (bullet_it != player->bulletList.end() && !hascolidWithBullet && !hasColidWithBomb) {
				hascolidWithBullet = HasCollidedBullet((*(*bullet_it)), (*it)->GetPosition().x, (*it)->GetPosition().y, (*it)->GetRadius());
				hasColidWithBomb = HasCollidedBonus((*bonus), (*it)->GetPosition().x, (*it)->GetPosition().y, (*it)->GetRadius(), bombExploding);
				bullet_it++;
			}
			if ((hascolidWithBullet || hasColidWithBomb) && drawBullet && (*it)->GetInvicibleTime() <= 0) {
				//enemy shield
				if ((*it)->GetHasShield()) {
					(*it)->UpdateHasShield();
					(*it)->SetInvicibleTime(0.2f);
				}
				//enemy life
				else if ((*it)->GetLife() > 1) {
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
				if ((*it)->type == EnemyType::DIVIDER ||
					(*it)->type == EnemyType::LIFEDIVIDER)
				{
					EnemyDivide((*it), enemyList);
				}

				if ((*it)->type == EnemyType::KAMIKAZE) {
					if ((*it)->GetHasExplode()) {
						EnemyDivide((*it), enemyList);
					}
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
				for (auto it = player->bulletList.begin(); it != player->bulletList.end(); it++) {
					window.draw((*it)->visual);
				}
			}
			window.draw(scoreText);

			if (drawBonus) {
				if (bonus->bonustype == BonusType::BOMB) {
					window.draw(bonus->bombShape);
				}
				else {
					window.draw(bonus->shape);
				}
			}
			if (drawBomb) {
				window.draw(bonus->bombShape);
			}
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

	while (!player->bulletList.empty()) {
		auto it = player->bulletList.begin();

		while (it != player->bulletList.end()) {
			delete (*it);
			it = player->bulletList.erase(it);
		}
		player->bulletList.clear();
	}

	delete player;

	//delete bullet;
}


void RainbowEffect(int& r, bool& addR) {
	if (addR) {
		r += 5;
		if (r > 255) {
			r = 255;
			addR = false;
		}
	}
	else
	{
		r -= 5;
		if (r < 0)
		{
			r = 0;
			addR = true;
		}
	}

}

void BombExpandEffect(float& s, bool& addS) {
	if (addS) {
		s += .05;
		if (s > 2) {
			addS = false;
		}
	}
	else {
		s -= .05;
		if (s <1) {
			addS = true;
		}
	}
}

void BombExplodEffect(float& s, Bonus* bonus) {
	bonus->bombShape.setFillColor(Color::Color(255, 188, 0));
	s += .4;
	if (s > 7) {
		s = 7;
	}
	bonus->bombShape.setScale(s, s);
}