#pragma once

#include <SFML/Graphics.hpp>;
#include <iostream>
#include <list>

#include "PlayerController.h"
#include "MathUtils.h"

using namespace std;
using namespace sf;

enum class EnemyType {
						//number	//description										//special feature
	BASIC,				// 0		//basic enemy										//shield, follow
	MINI,				// 1		//small deadly and high score						//
	TELEPORTER,			// 2		//teleporte onto last player location after time	//shield, follow
	SNAKE,				// 3		//sinus move pattern + tail							//shield, follow
	TAIL,				// 4		//tail of the snake									//
	KAMIKAZE,			// 5		//charge player and explode after time				//follow
	FOLLOWER,			// 6		//always follow player								//shield, follow
	DIVIDER,			// 7		//on destroy divide in multiple						//shield, follow, divide
	SUB,				// 8		//smaller enemy of divide							//
	LIFER,				// 9		//multiple life, become smaller on hit				//shield, follow
	LIFEDIVIDER			// 10		//multiple life, divide on hit						//shield, follow, divide
};
class EnemySubClass {
public:
	//variable
	CircleShape* shape = new CircleShape;			//Shape
	Vector2f spawnPoint = Vector2f(.0f, .0f);		//Spawn Point
	bool hasShield = false;							//Shield in shape -> blue outline
	int rotation = 0;								//Continuous rotation of shape
	Vector2f direction = Vector2f(.0f, .0f);		//Movement direction
	float speed = .0f;								//Movement speed
	bool isFollowingPlayer = false;					//Follow player or not
	bool canDivide = false;
	bool isAlive = true;
	int life = 1;
	float invicibleTime = .0f;
	int divideNumber = 0;
	bool hasExplode = false;

	//constructor && deconstructor
	EnemySubClass();
	virtual ~EnemySubClass();

	//method
	//Setter
	virtual void SetShape();																		//Default shape
	virtual void SetShape(float radius, int pointCount);											//for sub, divider, lifedivider
	virtual void SetShape(float radius, int pointCount, int life, int index, Vector2f parentPos);	//for lifedivider
	void SetShield();																				//Enemy can have an outline as a shield
	virtual void SetSpawnPoint(int width, int height);
	virtual void SetSubParameters(float radius, int divideNumber, Vector2f parentPos, int index);   //set speed, direction, spawn point etc...
	virtual void SetRotation();
	void SetDirection(int width, int height);
	void SetDirectionX(int width, int height);
	void SetDirectionY(int width, int height);
	virtual void SetSpeed();
	virtual void SetFollow();
	virtual void SetFollow(EnemyType type);
	void SetInvicibleTime(float value);

	//update
	void FollowPlayer(Player* pPlayer, float deltaTime);
	void LoopOnMap(int width, int height);
	virtual void Move(float deltaTime);
	virtual void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer);
	
	//getter
	virtual CircleShape* GetTeleportCircle();
	int GetDivideNumber();
	int GetLife();
	bool GetIsAlive();
	virtual float GetInvicibleTime();
	bool GetHasShield();
	bool GetHasExplode();
};
class Basic : public EnemySubClass {
public:
	//constructor & deconstructor
	Basic();
	~Basic();

	//method
	void SetShape() override;
};
class Teleporter : public EnemySubClass {
public:
	//variable
	float timeBeforeTeleport = 3.f;
	float stopMoveTime = .5f;
	float saveSpeed = .0f;
	Vector2f teleportPosition = Vector2f(.0f, .0f);
	bool gotPosition = false;
	CircleShape* teleportCircle = new CircleShape;
	float tCRadius = 10.0f;
	Color tCColor = Color(0, 0, 0, 50);
	Color tCOutline = Color(0, 0, 255, 150);

	//constructor & deconstructor
	Teleporter();
	~Teleporter();

	//method
	void SetShape() override;
	void SetSpeed() override;
	CircleShape* GetTeleportCircle() override;
	void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) override;
};
class Kamikaze : public EnemySubClass {
public:
	//variable
	float timerBeforeExplode = 3.0f;
	float stopMoveTime = 2.0f;

	//constructor & deconstructor
	Kamikaze();
	~Kamikaze();

	//method
	//Setter
	void SetShape() override;
	void SetSpeed() override;
	void SetFollow() override;
	void SetDivideNumber();

	//update
	void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) override;
};
class Mini : public EnemySubClass {
public:
	//variable

	//constructor & deconstructor
	Mini();
	~Mini();

	//method
	void SetShape() override;
};
class Snake : public EnemySubClass {
public:
	//variable
	float snakeX = 800.0f;
	float snakeY = .0f;
	int snakeLength = 5;
	list<CircleShape*> tail;

	//constructor & deconstructor
	Snake();
	~Snake();

	//method
	void SetShape() override;
	void SetSpawnPoint(int width, int height) override;
	void Move(float deltaTime) override;

};
class Tail : public EnemySubClass {
public : 
	//variable 

	//constructor & deconstructor
	Tail();
	~Tail();

	//method
	void SetShape() override;
};
class Follower : public EnemySubClass {
public:
	//variable

	//constructor & deconstructor
	Follower();
	~Follower();

	//method
	void SetShape() override;
	void SetSpeed() override;
	void SetFollow() override;
};
class Divider : public EnemySubClass {
public:
	//variable

	//constructor & deconstructor
	Divider();
	~Divider();

	//method
	void SetShape() override;
	void SetDivideNumber();
};
class Sub :public EnemySubClass {
public : 
	//variable

	//constructor & deconstructor
	Sub();
	~Sub();

	//method
	//Setter
	void SetShape(float radius, int pointCount) override;
	void SetSubParameters(float radius, int divideNumber,  Vector2f parentPos, int index) override;
	void SetFollow(EnemyType type) override;

	//update
	void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) override;
};
class Lifer : public EnemySubClass {
public :
	//variable

	//constructor & deconstrutor
	Lifer();
	~Lifer();

	//method
	//setter
	void SetShape() override;
	void SetLife();
};
class LifeDivider : public EnemySubClass {
public:	
	//variable

	//constructor & deconstructor
	LifeDivider();
	~LifeDivider();
	
	//method
	//setter
	void SetShape() override;
	void SetShape(float radius, int pointCount, int life, int index, Vector2f parentPos) override;
	void SetDivideNumber();
	void SetLife();
};
//INTERFACE
class Enemy {

public:
	//variable
	EnemyType type = EnemyType::BASIC;
	EnemySubClass* subClass = nullptr;
	bool isAlive = true;

	//constructor & deconstructor
	Enemy(Enemy* pEnemy, int index);
	Enemy(int width, int height);
	Enemy(int width, int height, EnemyType type);
	Enemy(float radius, int pointCount, int divideNumber, Vector2f parentPos, int index, EnemyType type, EnemyType parentType);
	~Enemy();

	//Method
	//Setter
	void SetType();
	void SetSubClass();
	void SetShape();
	void SetShape(float radius, int pointCount);
	void SetShape(float radius, int pointCount, int life, int index, Vector2f parentPos);
	void SetSpawnPoint(int widht, int height);
	void SetSubParameters(float radius, int divideNumber, Vector2f parentPos, int index);
	void SetSpeed();
	void SetDirection(int width, int height);
	void SetFollow(EnemyType parentType);
	void SetInvicibleTime(float value);

	//Getter
	CircleShape GetShape();
	CircleShape GetTeleportCircle();
	int GetDivideNumber();
	float GetRadius();
	int GetPointCount();
	Vector2f GetPosition();
	int GetLife();
	float GetInvicibleTime();
	bool GetHasShield();
	bool GetHasExplode();

	//update
	void UpdateHasShield();
	void UpdateLife();
	void UpdateInvicibleTime(float deltaTime);
	void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer);
};

