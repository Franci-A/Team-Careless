#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerController.h"

struct HealthIcon {
	sf::ConvexShape shape;
	sf::Text healthCount;
};
void InstantiateHealth(HealthIcon* health, int maxHealth, int width, sf::Font font);
void UpdateHealthText(Player player, HealthIcon* health, int width);