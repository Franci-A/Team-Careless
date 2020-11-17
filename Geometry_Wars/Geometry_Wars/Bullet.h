#pragma once
#include <list>
#include <map>
#include <SFML/Graphics.hpp>

enum class BALL_TYPE
{
	DEFAULT,
	TRIPLE,
	BIG,
	ACCELERATOR
};

struct Bullet
{
	int posX = 0;
	int posY = 0;

	int X_offset = 0;
	int Y_offset = 0;
	float speed = 0.0f;

	sf::CircleShape visual;

	BALL_TYPE type = BALL_TYPE::DEFAULT;

	float timer_StartPoint = 0.0f;
	float timer = 0.0f;
};

struct Bullet_Powerup
{
	BALL_TYPE type;
	sf::CircleShape visual;
	int speed;
	int ammo;
};

Bullet* SpawnBall(int playerX, int playerY, int cursorX, int cursorY, Bullet* newBall);

void UpdatePosition(Bullet* ball, float deltaTime);
void Check_Wall_Collision(Bullet* ball, int width, int height);

void InitializeBulletpedia(std::map<BALL_TYPE, Bullet_Powerup>& bulletpedia);