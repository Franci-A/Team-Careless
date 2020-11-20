#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerController.h"

struct HealthIcon {
	sf::ConvexShape shape;
};

void InstantiateHealth(HealthIcon* health,  int width);
void UpdateHealthText(Player player,sf::Text& text);