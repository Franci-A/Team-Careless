#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "DeltaTime.h"

struct Player {
	float speed = 650.0f;
	sf::CircleShape triangle;
	bool hasBullet = true;
	int life = 100;
	float invicibleTime = 0.0f;
	BALL_TYPE bulletType = BALL_TYPE::DEFAULT;
	std::list<Bullet*> bulletList;
	bool hasShield = false;
};

sf::Vector2f PlayerMove(Player& player, sf::Vector2f localPosition, float deltaTime, int screenWidth, int screenHeight);
void PlayerRotation(Player& player, sf::Vector2f localPosition);

void PlayerShot(bool& drawBullet, sf::Vector2f localPosition, Player player);

Bullet* AddNewBullet(Bullet_Powerup powerup);
void PowerupSwap(Player* player, std::map<BALL_TYPE, Bullet_Powerup> bulletpedia);