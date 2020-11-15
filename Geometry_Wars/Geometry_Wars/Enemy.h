#pragma once
#include <SFML/Graphics.hpp>;
#include <list>

#include "PlayerController.h"

using namespace std;
using namespace sf;

enum struct EnemyType {
	BASIC,
	MINI,
	TELEPORTER,
	SNAKE,
	KAMIKAZE,
	SUB		//sub enemy of the one that got destroy
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

	//behaviour
	int speed = 0;
	int rotation = 0;
	Vector2f velocity = Vector2f(0.0f ,0.0f);	

	//control
	bool isAlive = true;
	bool hasSpawn = false;

	//gameplay & ui
	int size = 0; //not real size -> for divide on destroy
	int life = 0;
	int scoreValue = 0;
	float invicibleTime = 0.0f;

	//SNAKE 
	float snakeX = 800.0f;
	float snakeY = 0.0f;
	int snakeLengt = 5;

};

struct Basic : Enemy {

};

struct Mini : Enemy {

};

struct Snake : Enemy {

};

struct Kamikaze : Enemy {

};

struct Teleporter : Enemy {

};
struct Sub : Enemy {

};

string EnemySetShapeType();
Vector2f EnemySetSpawnPoint(int width, int height, EnemyType type);
Color EnemySetColor(bool canDivide, int life, EnemyType type);
int EnemySetSpeed(EnemyType type);
int EnemySetRotation();
Vector2f EnemySetDirectionX(float x, int width, int height, float speed, EnemyType type);
Vector2f EnemySetDirectionY(float y, int width, int height, float speed, EnemyType type);
Vector2f EnemySetVelocity(float x, float y, int width, int height, float speed, EnemyType type);
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
