#pragma once
#include <SFML/Graphics.hpp>;
#include <list>
#include <vector>
#include <iostream>

#include "PlayerController.h"

using namespace std;
using namespace sf;

enum class EnemyType {
	BASIC,				// 0
	MINI,				// 1
	TELEPORTER,			// 2
	SNAKE,				// 3
	TAIL,				// 4  //tail of the snake
	KAMIKAZE,			// 5
	FOLLOWER,			// 6
	DIVIDER,			// 7 //on destroy divide in multiple
	SUB,				// 8 //smaller enemy of divide
	LIFER,				// 9 //multiple life, become smaller on hit
	LIFEDIVIDER			// 10 //multiple life, divide on hit
};

class EnemySubClass {
public :
	EnemySubClass();
	~EnemySubClass();
};

EnemySubClass::EnemySubClass() {

}

EnemySubClass::~EnemySubClass() {

}
class Basic : public EnemySubClass {
public:
	bool followPlayer;
	bool canDivide;
	bool hasOutline;

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

class Follower : public EnemySubClass {

};
class Divider : public EnemySubClass {
private:
public:
};

class Sub :public EnemySubClass {

};

class Lifer : public EnemySubClass {

};


class LifeDivider : public EnemySubClass {

};


class Enemy {

public:
	EnemyType type;
	CircleShape* shape;
	bool isAlive = true;

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
	float invicibleTime; //not multiple collision when divide

	//COMPOSITION
	EnemySubClass* enemySubClass = nullptr;
	//special feature
	bool followPlayer = false;
	bool canDivide = false;
	bool hasOutline = false;

	//Function
	Enemy();
	~Enemy();

	void SetType();
	void SetSubClass();
	virtual void SetRadius();
	virtual void SetShape();

};

Enemy::Enemy() {
	SetType();
	SetSubClass();
}
Enemy::~Enemy() {
	delete(this->shape);
	delete(this->enemySubClass);
}

void Enemy::SetType() {
	int rngEnemyType = rand() % 11;
	switch (rngEnemyType)
	{
	case 1:
		this->type = EnemyType::MINI;
		break;
	case 2:
		this->type = EnemyType::TELEPORTER;
		break;
	case 3:
		this->type = EnemyType::SNAKE;
		break;
	case 4:
		this->type = EnemyType::TAIL;
		break;
	case 5:
		this->type = EnemyType::KAMIKAZE;
		break;
	case 6:
		this->type = EnemyType::FOLLOWER;
		break;
	case 7:
		this->type = EnemyType::DIVIDER;
		break;
	case 8:
		this->type = EnemyType::SUB;
		break;
	case 9:
		this->type = EnemyType::LIFER;
		break;
	case 10:
		this->type = EnemyType::LIFEDIVIDER;
		break;
	default:
		this->type = EnemyType::BASIC;
		break;
	}
}
void Enemy::SetSubClass() {
	switch (this->type)
	{
	case EnemyType::BASIC:
		this->enemySubClass = new Basic;
		break;
	case EnemyType::MINI:
		this->enemySubClass = new Mini;
		break;
	case EnemyType::TELEPORTER:
		this->enemySubClass = new Teleporter;
		break;
	case EnemyType::SNAKE:
		this->enemySubClass = new Snake;
		break;
	case EnemyType::TAIL:
		this->enemySubClass = new Tail;
		break;
	case EnemyType::KAMIKAZE:
		this->enemySubClass = new Kamikaze;
		break;
	case EnemyType::FOLLOWER:
		this->enemySubClass = new Follower;
		break;
	case EnemyType::DIVIDER:
		this->enemySubClass = new Divider;
		break;
	case EnemyType::SUB:
		this->enemySubClass = new Sub;
		break;
	case EnemyType::LIFER:
		this->enemySubClass = new Lifer;
		break;
	case EnemyType::LIFEDIVIDER:
		this->enemySubClass = new LifeDivider;
		break;
	default:
		break;
	}
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



//string EnemySetShapeType();
//Vector2f EnemySetSpawnPoint(int width, int height, EnemyType type);
//Color EnemySetColor(bool canDivide, int life, EnemyType type);
//int EnemySetSpeed(EnemyType type);
//int EnemySetRotation();
//Vector2f EnemySetDirectionX(float x, int width, int height, float speed, EnemyType type);
//Vector2f EnemySetDirectionY(float y, int width, int height, float speed, EnemyType type);
//Vector2f EnemySetVelocity(float x, float y, int width, int height, float speed, EnemyType type);
//float EnemySetRadius(EnemyType type, int life);
//void EnemySetShape(Enemy* pEnemy, CircleShape* pShape);
//int EnemySetLife(EnemyType type);
//int EnemySetSize(float radius);
//int EnemySetScoreValue(float radius, EnemyType type);
//bool EnemySetHasOutline(EnemyType type);
//bool EnemySetFollowPlayer(EnemyType type);
//bool EnemySetCanDivide(EnemyType type);
//EnemyType EnemySetType();
//
//Enemy* EnemyCreate(int width, int height);
//void EnemyUpdate(Enemy* pEnemy, int width, int height, float deltaTime, float deltaAngle, Player* pPlayer, list<Enemy*>& enemyList);
//
//void EnemyDivide(Enemy* enemy, list<Enemy*>& pEnemyList, int width, int height);
//void EnemyDivideSetParameters(Enemy* divide, Enemy* enemy, int count);
//void EnemyFollowPlayer(Enemy* pEnemy, Player* pPlayer, float deltaTime);
//
//Enemy* EnemySnakeTail(Enemy*);


//TriggerExit
//bool hasCollid = false;
//has collid = true on collision 
// if hit enemy = false
//hasCollide = true && in main has collid = false
//has collidde  =false;
//