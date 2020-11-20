#include "Bonus.h"
#include <stdlib.h>



void SpawnBonus(Bonus* bonus, int width, int height, bool& drawBonus) {
	int offset = 200;
	sf::Vector2f spawnPosition;
	int bonusToSpawn = rand() % 6;
	switch (bonusToSpawn)
	{
	case 0:
		BonusTypeShield(bonus);
		break;
	case 1:
		BonusTypeSpeedUp(bonus);
		break;
	case 2:
		BonusTypeLifeUp(bonus);
		break;
	case 3:
		BonusTypeInvincibil(bonus);
		break;
	case 4:
		BonusTypeBomb(bonus);
		break;
	case 5:
		BonusTypeBulletSwap(bonus);
		break;
	}
	

	spawnPosition.x = offset + rand() % (width - offset*2);
	spawnPosition.y = offset + rand() % (height - offset*2);
	bonus->shape.setPosition(spawnPosition);
	bonus->bombShape.setPosition(spawnPosition);
	drawBonus = true;
}

void BonusCollected(Bonus* bonus, Player* player, float elapsedTime, std::map<BALL_TYPE, Bullet_Powerup> bulletpedia) {
	bonus->timer = elapsedTime;
	switch (bonus->bonustype) {
	case BonusType::SHEILD:
		player->triangle.setOutlineThickness(3);
		player->triangle.setOutlineColor(sf::Color::Blue/*sf::Color::Color(51, 174, 255)*/);
		player->hasShield = true;
		break;
	case BonusType::LIFEUP:
		player->life++;
		break;
	case BonusType::SPEED:
		player->triangle.setOutlineThickness(3);
		player->triangle.setOutlineColor(sf::Color::Color(252, 255, 51));
		player->speed += 300;
		bonus->bonusTimer = elapsedTime;
		break;
	case BonusType::INVINCIBIL:
		bonus->bonusTimer = elapsedTime;
		player->speed += 200;
		break;
	case BonusType::BOMB:
		bonus->bonusTimer = elapsedTime;
		player->triangle.setOutlineThickness(3);
		player->triangle.setOutlineColor(sf::Color::Color(90, 90, 90));
		break;
	case BonusType::BULLETSWAP:
		PowerupSwap(player, bulletpedia);
		break;
	}
}

void BonusTypeShield(Bonus* bonus) {
	bonus->bonustype = BonusType::SHEILD;
	bonus->shape.setPointCount(7);
	bonus->shape.setPoint(0, sf::Vector2f(0, 0));
	bonus->shape.setPoint(1, sf::Vector2f(30, 0));
	bonus->shape.setPoint(2, sf::Vector2f(30, 25));
	bonus->shape.setPoint(3, sf::Vector2f(28, 30));
	bonus->shape.setPoint(4, sf::Vector2f(15, 40));
	bonus->shape.setPoint(5, sf::Vector2f(2,30));
	bonus->shape.setPoint(6, sf::Vector2f(0,25));
	bonus->shape.setOrigin(15, 20);
	bonus->shape.setScale(1.2, 1.2);
	bonus->shape.setFillColor(sf::Color::Color(51 ,174,255));
}

void BonusTypeLifeUp(Bonus* bonus) {
	bonus->bonustype = BonusType::LIFEUP;
	bonus->shape.setPointCount(8);
	bonus->shape.setPoint(0, sf::Vector2f(15, 10));
	bonus->shape.setPoint(1, sf::Vector2f(19, 0));
	bonus->shape.setPoint(2, sf::Vector2f(26, 0));
	bonus->shape.setPoint(3, sf::Vector2f(30, 12));
	bonus->shape.setPoint(4, sf::Vector2f(15, 30));
	bonus->shape.setPoint(5, sf::Vector2f(0, 12));
	bonus->shape.setPoint(6, sf::Vector2f(4, 0));
	bonus->shape.setPoint(7, sf::Vector2f(11, 0));
	bonus->shape.setOrigin(15, 15);
	bonus->shape.setScale(1.2, 1.2);
	bonus->shape.setFillColor(sf::Color::Color(255, 70, 51));
}

void BonusTypeSpeedUp(Bonus* bonus) {
	bonus->bonustype = BonusType::SPEED;
	bonus->shape.setPointCount(6);
	bonus->shape.setPoint(0, sf::Vector2f(23, 0));
	bonus->shape.setPoint(1, sf::Vector2f(15, 18));
	bonus->shape.setPoint(2, sf::Vector2f(30, 16));
	bonus->shape.setPoint(3, sf::Vector2f(7, 40));
	bonus->shape.setPoint(4, sf::Vector2f(15, 22));
	bonus->shape.setPoint(5, sf::Vector2f(0, 24));
	bonus->shape.setOrigin(15, 20);
	bonus->shape.setScale(1.2, 1.2);
	bonus->shape.setFillColor(sf::Color::Color(252, 255, 51));
}

void BonusTypeInvincibil(Bonus* bonus) {
	bonus->bonustype = BonusType::INVINCIBIL;
	bonus->shape.setPointCount(10);
	bonus->shape.setPoint(0, sf::Vector2f(20, 0));
	bonus->shape.setPoint(1, sf::Vector2f(26, 13));
	bonus->shape.setPoint(2, sf::Vector2f(40, 16));
	bonus->shape.setPoint(3, sf::Vector2f(30, 25));
	bonus->shape.setPoint(4, sf::Vector2f(32, 40));
	bonus->shape.setPoint(5, sf::Vector2f(20, 30));
	bonus->shape.setPoint(6, sf::Vector2f(8, 40));
	bonus->shape.setPoint(7, sf::Vector2f(10, 25));
	bonus->shape.setPoint(8, sf::Vector2f(0, 16));
	bonus->shape.setPoint(9, sf::Vector2f(14,13));
	bonus->shape.setOrigin(15, 20);
	bonus->shape.setScale(1.2, 1.2);
	bonus->shape.setFillColor(sf::Color::Color(252, 255, 51));
}

void BonusTypeBomb(Bonus* bonus) {
	bonus->bonustype = BonusType::BOMB;
	bonus->bombShape.setRadius(20);
	bonus->bombShape.setOrigin(20, 20);
	bonus->bombShape.setScale(1.2, 1.2);
	bonus->bombShape.setFillColor(sf::Color::Color(90, 90, 90));
	bonus->bombShape.setOutlineThickness(0);
}

void PlaceBomb(sf::Vector2f localPosition, Bonus* bonus, bool& drawBomb , Player* player) {
	bonus->bombShape.setPosition(localPosition);
	drawBomb = true;
	player->triangle.setOutlineThickness(0);
}

void BonusTypeBulletSwap(Bonus* bonus) {
	bonus->bonustype = BonusType::BULLETSWAP;
	bonus->bombShape.setFillColor(sf::Color::Transparent);
	bonus->bombShape.setRadius(15);
	bonus->bombShape.setOrigin(15, 15);
	bonus->bombShape.setScale(1.2, 1.2);
	bonus->bombShape.setOutlineColor(sf::Color::Green);
	bonus->bombShape.setOutlineThickness(7);
}