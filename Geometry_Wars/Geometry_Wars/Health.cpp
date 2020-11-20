#include "Health.h"
#include <list>

void InstantiateHealth(HealthIcon* health ,int maxHealth, int width, sf::Font font, sf::Text& text) {
	health->shape.setFillColor(sf::Color::Red);
	health->shape.setPointCount(8);
	health->shape.setPoint(0, sf::Vector2f(15, 10));
	health->shape.setPoint(1, sf::Vector2f(19, 0));
	health->shape.setPoint(2, sf::Vector2f(26, 0));
	health->shape.setPoint(3, sf::Vector2f(30, 12));
	health->shape.setPoint(4, sf::Vector2f(15, 30));
	health->shape.setPoint(5, sf::Vector2f(0, 12));
	health->shape.setPoint(6, sf::Vector2f(4, 0));
	health->shape.setPoint(7, sf::Vector2f(11, 0));
	health->shape.setScale(1.5, 1.5);
	health->shape.setPosition(width - health->shape.getLocalBounds().width *2, 10);
	text.setFont(font);
	text.setString(std::to_string(maxHealth));
	text.setCharacterSize(100);
	text.setPosition(width - health->shape.getPosition().x - text.getLocalBounds().width, 10);

	return ;
}

sf::Text UpdateHealthText(Player player, int width) {
	sf::Text text;
	text.setString(std::to_string(player.life));
	return text;
}