#pragma once

#include <SFML/Graphics.hpp>
#include "MathUtils.h"
#include "EnemyClass.h"

class VFX {
public:
	//variable
	CircleShape circle;
	float speed = 100.0f;
	int radius = 10;
	Vector2f direction = Vector2f(0.f, 0.f);
	float time = 0.2f;
	bool isAlive = true;

	void move(float deltaTime);
	//constructor & deconstructor
	VFX(int divideEnemy, Enemy* pEnemy, int i);
	~VFX();
};