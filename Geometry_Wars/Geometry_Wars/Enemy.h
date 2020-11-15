#pragma once
#include <SFML/Graphics.hpp>;
#include <list>
using namespace std;
using namespace sf;

enum class EnemyType {
	BASIC,
	MINI,
	TELEPORT,
	SNAKE,
	DIVIDER
};
struct Enemy {

	//type
	EnemyType enemyType = EnemyType::BASIC;

	//special feature
	bool followPlayer = false;
	bool canDivide = false;
	bool hasOutline = false;

	//shape
	string shapeType = "Circle";
	Color color = Color::Red;
	Vector2f spawnPoint = Vector2f(0.0f ,0.0f);
	CircleShape shape;
	float radius = 0.0f;
	int angle = 0;

	//behaviour
	int speed = 0;
	int rotation = 0;
	Vector2f velocity = Vector2f(0.0f ,0.0f);	

	//control
	bool isAlive = true;
	bool hasSpawn = false;
	bool isInvicible = false;

	//divide, life, score
	int size = 0; //not real size -> for divide on destroy
	int life = 0;
	int scoreValue = 0;
	float invicibleTime = 0.0f;
};

string EnemySetShapeType();
Vector2f EnemySetSpawnPoint(int width, int height);
Color EnemySetColor(bool canDivide, int life);
int EnemySetSpeed();
int EnemySetRotation();
Vector2f EnemySetVelocity(float x, float y, int width, int height, float speed);
int EnemySetAngle();
float EnemySetRadius();
void EnemySetShape(Enemy* pEnemy, CircleShape* pShape);
int EnemySetLife();
int EnemySetSize(float radius);
int EnemySetScoreValue(float radius);
Enemy* EnemyCreate(int width, int height);
void EnemyUpdate(Enemy* pEnemy, int width, int height, float deltaTime, float deltaAngle);
Vector2f EnemySetDirectionX(float x, int width, int height, float speed);
void EnemyDivide(Enemy* enemy, list<Enemy*>& pEnemyList, int width, int height);
void EnemyDivideSetParameters(Enemy* divide, Enemy* enemy, int count);
