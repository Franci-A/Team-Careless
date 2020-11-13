#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>;
#include <math.h>

using namespace std;
using namespace sf;

struct Enemy {

	CircleShape shape;
	string shapeType;
	Color color;
	Vector2f spawnPoint;
	Vector2f velocity;
	FloatRect hitBox;
	float speed;
	float rotationSpeed;
	float angle;	
	float radius = 50.0f;
	float size; //not real size for score and division if destroy
	int life = 1;
	bool isAlive = true;
	bool hasSpawn = false;
};

string EnemySetShapeType();
Vector2f EnemySetSpawnPoint(int width, int height);
Color EnemySetColor();
float EnemySetSpeed();
float EnemySetRotationSpeed();
float EnemySetAngle(float w, float h, float width, float height);
Vector2f EnemySetVelocity(float w, float h, float width, float height, float speed);
int EnemySetRadius();
Enemy EnemyCreate(int width, int height);
CircleShape CreateEnemyShape(Enemy enemy);
void EnemyUpdatePosition();
Enemy* EnemyDCreate(int width, int height);
void EnemySetForme(Enemy* enemy, CircleShape* shape);