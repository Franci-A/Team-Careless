#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"

struct Player {
	float speed = .5f;
	sf::CircleShape triangle;
	bool hasBullet = true;
};

void PlayerMove(Player& player, sf::Vector2f localPosition, float deltaTime);
void PlayerRotation(Player& player, sf::Vector2f localPosition);
Bullet* PlayerShot(bool& drawBullet, sf::Vector2f localPosition, Player player,  Bullet* bullet);