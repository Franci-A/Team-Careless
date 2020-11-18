#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerController.h"
enum BonusType { SHEILD, SPEED, LIFEUP,DASH, INVINCIBIL,  BOMB};

struct Bonus {
	sf::ConvexShape shape;
	BonusType bonustype;
	float timer = 0;
	float speedTimer = 0;
	float invincibleTimer = 0;
};

void SpawnBonus(Bonus* bonus, int width, int height, bool &drawBonus);
void BonusTypeShield(Bonus* bonus);
void BonusCollected(Bonus* bonus, Player* player, float elapsedTime);
void BonusTypeLifeUp(Bonus* bonus);
void BonusTypeSpeedUp(Bonus* bonus);
void BonusTypeInvincibil(Bonus* bonus);