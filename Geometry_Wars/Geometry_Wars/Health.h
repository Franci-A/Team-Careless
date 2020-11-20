#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerController.h"

struct HealthIcon {
	sf::ConvexShape shape;
};

void InstantiateHealth(HealthIcon* health, int maxHealth, int width, sf::Font font, sf::Text& text);
sf::Text UpdateHealthText(Player player, int width);