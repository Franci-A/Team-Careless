#pragma once
#include <SFML/Graphics.hpp>;
#include <list>
#include <vector>
#include <iostream>

#include "PlayerController.h"

using namespace std;
using namespace sf;

enum class EnemyType {
	BASIC,
	MINI,
	TELEPORTER,
	SNAKE,
	TAIL, //tail of the snake
	KAMIKAZE,
	DIVIDE,	//sub enemy of the one that got destroy (divide)
};

class EnemySubClass {

};
class Basic : public EnemySubClass {
private:
	bool followPlayer;
	bool canDivide;
	bool hasOutline;

public:
	Basic();
};

Basic::Basic() {
	cout << "basic creation" << endl;
}

class Teleporter : public EnemySubClass {
private:
	float timeBeforeTeleport = 5.0f;
	Vector2f teleportPosition = Vector2f(-1.0f, -1.0f);
	CircleShape teleportCircle;
public:
};

class Kamikaze : public EnemySubClass {
private:
	float timerBeforeExplode = 5.0f;

public:
};

class Mini : public EnemySubClass {
private:
public:

};

class Snake : public EnemySubClass {
private:
	float snakeX;
	float snakeY;
	int snakeLength = 5;
	list<CircleShape*> tail;

public:

};

class Tail : public EnemySubClass {
private:
public:
};

class Divide : public EnemySubClass {
private:
public:
};

class Enemy {
private:

	string shapeType;
	Color color;
	Vector2f spawnPoint;
	Vector2f velocity;

	float radius;
	int speed;
	int rotation;

	int size;
	int life;
	int scoreValue;
	float invicibleTime; //not multiple collision

	//COMPOSITION
	EnemySubClass* enemySubClass;
	
public:
	EnemyType type;
	CircleShape* shape;
	bool isAlive = true;
	//bool hasSpawn = false;

	//special feature
	bool followPlayer = false;
	bool canDivide = false;
	bool hasOutline = false;

	Enemy();
	~Enemy();
	//set type
	//depending of type
	//create corresponding enemy
	//need to add parameters ???
};

Enemy::Enemy() {
	switch (type)
	{
	case EnemyType::BASIC:
		break;
	case EnemyType::MINI:
		break;
	case EnemyType::TELEPORTER:
		break;
	case EnemyType::SNAKE:
		break;
	case EnemyType::TAIL:
		break;
	case EnemyType::KAMIKAZE:
		break;
	case EnemyType::DIVIDE:
		break;
	default:
		break;
	}
	//this->teleporter = 
}
Enemy::~Enemy() {
	delete(this->shape);
}

//struct Enemy {
//
//	//type
//	EnemyType type = EnemyType::BASIC;
//
//	//special feature
//	bool followPlayer = false;
//	bool canDivide = false;
//	bool hasOutline = false;
//
//	//shape
//	string shapeType = "Circle";
//	Color color = Color::Red;
//	Vector2f spawnPoint = Vector2f(0.0f ,0.0f);
//	CircleShape shape;
//	float radius = 0.0f;
//
//	//behaviour
//	int speed = 0;
//	int rotation = 0;
//	Vector2f velocity = Vector2f(0.0f ,0.0f);	
//
//	//control
//	bool isAlive = true;
//	bool hasSpawn = false;
//
//	//gameplay & ui
//	int size = 0; //not real size -> for divide on destroy
//	int life = 0;
//	int scoreValue = 0;
//	float invicibleTime = 0.0f;
//
//	//SNAKE 
//	float snakeX = 800.0f;
//	float snakeY = 0.0f;
//	int snakeLength = 5;
//	int snakeID = 0;
//	vector<CircleShape> tail;
//
//	//TELEPORT
//	float timeBeforeTeleport = 5.0f;
//	Vector2f teleportPosition = Vector2f(-1.0f, -1.0f);
//	CircleShape teleportCircle;
//
//	//KAMIKAZE
//	float timerBeforeExplode = 5.0f;
//
//	//TELEPORT et KAMIKAZE
//	float stopMoveTime = 2.0f;
//};



string EnemySetShapeType();
Vector2f EnemySetSpawnPoint(int width, int height, EnemyType type);
Color EnemySetColor(bool canDivide, int life, EnemyType type);
int EnemySetSpeed(EnemyType type);
int EnemySetRotation();
Vector2f EnemySetDirectionX(float x, int width, int height, float speed, EnemyType type);
Vector2f EnemySetDirectionY(float y, int width, int height, float speed, EnemyType type);
Vector2f EnemySetVelocity(float x, float y, int width, int height, float speed, EnemyType type);
float EnemySetRadius(EnemyType type, int life);
void EnemySetShape(Enemy* pEnemy, CircleShape* pShape);
int EnemySetLife(EnemyType type);
int EnemySetSize(float radius);
int EnemySetScoreValue(float radius, EnemyType type);
bool EnemySetHasOutline(EnemyType type);
bool EnemySetFollowPlayer(EnemyType type);
bool EnemySetCanDivide(EnemyType type);
EnemyType EnemySetType();

Enemy* EnemyCreate(int width, int height);
void EnemyUpdate(Enemy* pEnemy, int width, int height, float deltaTime, float deltaAngle, Player* pPlayer, list<Enemy*>& enemyList);

void EnemyDivide(Enemy* enemy, list<Enemy*>& pEnemyList, int width, int height);
void EnemyDivideSetParameters(Enemy* divide, Enemy* enemy, int count);
void EnemyFollowPlayer(Enemy* pEnemy, Player* pPlayer, float deltaTime);

Enemy* EnemySnakeTail(Enemy*);


//TriggerExit
//bool hasCollid = false;
//has collid = true on collision 
// if hit enemy = false
//hasCollide = true && in main has collid = false
//has collidde  =false;
//