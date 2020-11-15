#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include"DeltaTime.h"

struct Player {
	float speed = 400.0f;
	sf::CircleShape triangle;
	bool hasBullet = true;
	int life = 100;
	float invicibleTime = 0.0f;
};

sf::Vector2f PlayerMove(Player& player, sf::Vector2f localPosition, float deltaTime);
void PlayerRotation(Player& player, sf::Vector2f localPosition);
Bullet* PlayerShot(bool& drawBullet, sf::Vector2f localPosition, Player player,  Bullet* bullet);