#pragma once
#include <SFML/Graphics.hpp>


struct Player {
	float speed = .1f;
	sf::CircleShape triangle;
};

void PlayerMove(Player& player, sf::Vector2f localPosition, float deltaTime);
void PlayerRotation(Player& player, sf::Vector2f localPosition);