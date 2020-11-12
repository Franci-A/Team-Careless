#pragma once
#include <SFML/Graphics.hpp>



enum BALL_TYPE
{
	DEFAULT
	// si Bonus . . .
};

struct Bullet
{
	int posX;
	int posY;

	int X_offset = 0;
	int Y_offset = 0;
	float speed;

	sf::CircleShape visual;

	BALL_TYPE type;

	float timer_StartPoint;
	float timer = 0.0f;
};


Bullet* SpawnBall(int playerX, int playerY, int cursorX, int cursorY, BALL_TYPE type, Bullet* newBall);

void UpdatePosition(Bullet* ball);


void Check_Wall_Collision(Bullet* ball, int width, int height);

