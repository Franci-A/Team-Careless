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
	gameover.setString("Game Over");
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

	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window"); //, Style::Fullscreen
	window.setFramerateLimit(60);

	// Game loop
	while (window.isOpen()) {
		Event event;
		//Delta Time
		deltaTime = clockDelta.getElapsedTime().asSeconds();
		clockDelta.restart();
		//Player Movement
		Vector2f localPosition = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		Vector2f starsMove;
		if (Mouse::isButtonPressed(Mouse::Right) && (player->triangle.getPosition().x + 20 != localPosition.x || player->triangle.getPosition().y + 20 != localPosition.y) && !defeat)
		{
			//Background Parallax
			starsMove = PlayerMove((*player), localPosition, deltaTime);
			stars1.move(- starsMove.x /2 , - starsMove.y /2);
			background.move(- starsMove.x /5 , - starsMove.y /5);
		}
		//Player face cursor
		PlayerRotation((*player), localPosition); 

		//Fire!
		if (Mouse::isButtonPressed(Mouse::Left) && !drawBullet) {
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
		}

		//ENEMY Functions
#pragma region Create Enemy
		elapsedTimeSpawn = clockSpawn.getElapsedTime();
		if (elapsedTimeSpawn.asSeconds() > spawnTime && countEnemy < maxEnemy)
		{
			Enemy* enemi = new Enemy;
			enemi = EnemyCreate(width, height);
			enemyList.push_back(enemi);

			clockSpawn.restart();
			countEnemy++;
		}
#pragma endregion
#pragma region Update Enemy
		//MOVE & COLLISION & ALIVE & SCORE
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			deltaAngle = deltaTime * IIM_PI * 2.0f * (*it)->rotation;
			EnemyUpdate(*it, width, height, deltaTime, deltaAngle);

			//collision Player -> enemy
			bool hascolidWithplayer = HasCollided((*player), (*it)->shape.getPosition().x, (*it)->shape.getPosition().y, (*it)->radius);
			if (hascolidWithplayer) {
				defeat = true;
				drawBullet = false;
			}

			//collision bullet -> enemy
			bool hascolidWithBullet = HasCollidedBullet((*bullet), (*it)->shape.getPosition().x, (*it)->shape.getPosition().y, (*it)->radius);
			if (hascolidWithBullet && drawBullet && (*it)->invicibleTime <= 0) {

				//enemy shield
				if ((*it)->hasOutline) {
					(*it)->shape.setOutlineThickness(0);
					(*it)->hasOutline = false;
					(*it)->invicibleTime = 0.5f;
				}
				//enemy life
				else if((*it)->life > 0) {
					(*it)->life--;
				}
				//Dead
				else {
					(*it)->isAlive = false;
					//Update score
					score += (*it)->scoreValue;
					scoreText.setString(to_string(score));
				}
			}
			
			if (hascolidWithBullet && drawBullet && (*it)->invicibleTime <= 0) {

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

		//remove invicible
		for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
			if ((*it)->invicibleTime > 0) {
				(*it)->invicibleTime -= deltaTime;
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
					window.draw((*it)->shape);
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