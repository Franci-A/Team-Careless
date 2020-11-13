#pragma once
#include <SFML/Graphics.hpp>

enum BALL_TYPE
{
	DEFAULT
	// si Bonus . . .
};

struct Bullet
{
	int posX = 0;
	int posY = 0;

	int X_offset = 0;
	int Y_offset = 0;
	float speed = 0.0f;

	sf::CircleShape visual;

	BALL_TYPE type = DEFAULT;

	float timer_StartPoint = 0.0f;
	float timer = 0.0f;
};


Bullet* SpawnBall(int playerX, int playerY, int cursorX, int cursorY, BALL_TYPE type, Bullet* newBall);

void UpdatePosition(Bullet* ball, float deltaTime);


void Check_Wall_Collision(Bullet* ball, int width, int height);

