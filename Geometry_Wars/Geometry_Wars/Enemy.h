#pragma once
#include <SFML/Graphics.hpp>;
#include <list>

#include "PlayerController.h"

using namespace std;
using namespace sf;

enum class EnemyType {
	BASIC,
	MINI,
	TELEPORT,
	SNAKE,
	KAMIKAZE
};
struct Enemy {

	//type
	EnemyType type = EnemyType::BASIC;

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

	//divide, life, score
	int size = 0; //not real size -> for divide on destroy
	int life = 0;
	int scoreValue = 0;
	float invicibleTime = 0.0f;
};

string EnemySetShapeType();
Vector2f EnemySetSpawnPoint(int width, int height);
Color EnemySetColor(bool canDivide, int life, EnemyType type);
int EnemySetSpeed(EnemyType type);
int EnemySetRotation();
Vector2f EnemySetDirectionX(float x, int width, int height, float speed, EnemyType type);
Vector2f EnemySetDirectionY(float y, int width, int height, float speed, EnemyType type);
Vector2f EnemySetVelocity(float x, float y, int width, int height, float speed, EnemyType type);
int EnemySetAngle();
float EnemySetRadius(EnemyType type);
void EnemySetShape(Enemy* pEnemy, CircleShape* pShape);
int EnemySetLife(EnemyType type);
int EnemySetSize(float radius);
int EnemySetScoreValue(float radius, EnemyType type);
bool EnemySetHasOutline(EnemyType type);
bool EnemySetFollowPlayer(EnemyType type);
bool EnemySetCanDivide(EnemyType type);
EnemyType EnemySetType();

Enemy* EnemyCreate(int width, int height);
void EnemyUpdate(Enemy* pEnemy, int width, int height, float deltaTime, float deltaAngle, Player* pPlayer);

void EnemyDivide(Enemy* enemy, list<Enemy*>& pEnemyList, int width, int height);
void EnemyDivideSetParameters(Enemy* divide, Enemy* enemy, int count);
void EnemyFollowPlayer(Enemy* pEnemy, Player* pPlayer, float deltaTime);
