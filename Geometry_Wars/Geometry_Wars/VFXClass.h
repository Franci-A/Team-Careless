#pragma once

#include <SFML/Graphics.hpp>
#include "MathUtils.h"
#include "EnemyClass.h"

class VFX {
public:
	//variable
	CircleShape shape;
	float speed = 25.0f;
	int radius = 15;
	float radiusReduc = 0.8f;
	Vector2f direction = Vector2f(0.f, 0.f);
	float time = (rand() % (10 - 4) + 4) * 0.1f;
	bool isAlive = true;

	void move(float deltaTime);
	//constructor & deconstructor
	VFX(int divideEnemy, Enemy* pEnemy, int i);
	VFX(Player* pPlayer, bool invicibleBonus);
	~VFX();
};