#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerController.h"

enum BonusType { SHEILD, SPEED, LIFEUP, INVINCIBIL,  BOMB, BULLETSWAP};

struct Bonus {
	sf::ConvexShape shape;
	sf::CircleShape bombShape;
	BonusType bonustype;
	float timer = 0;
	float bonusTimer = 0;
};

void SpawnBonus(Bonus* bonus, int width, int height, bool &drawBonus);
void BonusTypeShield(Bonus* bonus);
void BonusCollected(Bonus* bonus, Player* player, float elapsedTime, std::map<BALL_TYPE, Bullet_Powerup> bulletpedia);
void BonusTypeLifeUp(Bonus* bonus);
void BonusTypeSpeedUp(Bonus* bonus);
void BonusTypeInvincibil(Bonus* bonus);
void BonusTypeBomb(Bonus* bonus);
void PlaceBomb(sf::Vector2f localPosition, Bonus* bonus, bool& drawBomb,Player* player);
void BonusTypeBulletSwap(Bonus* bonus);