#pragma once
#include <SFML/Graphics.hpp>;

using namespace std;
using namespace sf;

struct Enemy {

	string shapeType = "Circle";
	Color color = Color::Red;
	Vector2f spawnPoint = Vector2f(0.0f ,0.0f);
	CircleShape shape;
	float radius = 0.0f;
	int angle = 0;

	float speed = 0.0f;
	float rotationSpeed = 0.0f;
	Vector2f velocity = Vector2f(0.0f ,0.0f);	

	bool isAlive = true;
	bool hasSpawn = false;


	int size = 0; //not real size -> for divide on destroy
	int life = 0;
	int scoreValue = 0;
};

string EnemySetShapeType();
Vector2f EnemySetSpawnPoint(int width, int height);
Color EnemySetColor();
float EnemySetSpeed();
float EnemySetRotationSpeed();
Vector2f EnemySetVelocity(float w, float h, int width, int height, float speed);
int EnemySetAngle();
float EnemySetRadius();
void EnemySetShape(Enemy* pEnemy, CircleShape* pShape);
int EnemySetLife();
int EnemySetSize(float radius);
int EnemySetScoreValue();
Enemy* EnemyCreate(int width, int height);
void EnemyUpdate(Enemy* pEnemy, int width, int height);
