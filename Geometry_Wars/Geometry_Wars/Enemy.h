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

#pragma region EnemySubClass
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
	float invicibleTime = 0.f;
	//constructor && deconstructor
	EnemySubClass();
	virtual ~EnemySubClass();

	//method
	virtual void SetShape();		//Default shape
	virtual void SetShape(float radius, int pointCount) {}
	void SetShield();		//Enemy can have an outline as a shield
	virtual void SetSpawnPoint(int width, int height);
	virtual void SetSubParameters(float radius, int divideNumber, Vector2f parentPos, int index) {}
	virtual void SetRotation();
	void SetDirection(int width, int height);
	void SetDirectionX(int width, int height);
	void SetDirectionY(int width, int height);
	virtual void SetSpeed();
	virtual void Move(float deltaTime) {
		this->shape->move(this->direction * this->speed * deltaTime);
	}
	virtual void SetFollow();
	virtual void SetFollow(EnemyType type){}
	void FollowPlayer(Player* pPlayer, float deltaTime);
	void LoopOnMap(int width, int height);
	virtual void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) {
		this->shape->rotate(deltaAngle * rotation);
		if (isFollowingPlayer == true) {
			FollowPlayer(pPlayer, deltaTime);
		}
		else {
			Move(deltaTime);
		}
		LoopOnMap(width, height);
	};
	
	virtual CircleShape* GetTeleportCircle() {
		return nullptr;
	}

	virtual int GetDivideNumber() {
		return 0;
	}
	int GetLife() {
		return this->life;
	}
	bool GetIsAlive() {
		return this->isAlive;
	}
	virtual float GetInvicibleTime() {
		return this->invicibleTime;
	}
	bool GetHasShield() {
		return this->hasShield;
	}
};

//constructor
EnemySubClass::EnemySubClass() {
	SetRotation();
}

//destructor
EnemySubClass::~EnemySubClass() {
	delete shape;
}

//method
void EnemySubClass::SetShape() {
	this->shape->setRadius(50);
	this->shape->setOrigin(shape->getRadius(), shape->getRadius());
	this->shape->setFillColor(Color::Red);
}

void EnemySubClass::SetShield() {
	int rngShield = rand() % 10;	//1/10 have shield
	float outlineThickness = 10.0f;
	Color color(0, 126, 178);
	if (rngShield == 1) {
		this->hasShield = true;
	}

	if (this->hasShield) {
		this->shape->setOutlineThickness(outlineThickness);
		this->shape->setOutlineColor(color);
	}
}

void EnemySubClass::SetSpawnPoint(int width, int height) {
	float rngWidth = static_cast<float>(rand() % width);
	float rngHeight = static_cast<float>(rand() % height);
	int rngWallSpawn = rand() % 4 + 1;

	//UP
	if (rngWallSpawn == 1) {
		this->spawnPoint = Vector2f(rngWidth, 0);
	}
	//RIGHT
	else if (rngWallSpawn == 2) {
		this->spawnPoint = Vector2f(static_cast<float>(width), rngHeight);
	}
	//DOWN
	else if (rngWallSpawn == 3) {
		this->spawnPoint = Vector2f(rngWidth, static_cast<float>(height));
	}
	//LEFT
	else if (rngWallSpawn == 4) {
		this->spawnPoint = Vector2f(0, rngHeight);
	}

	this->shape->setPosition(spawnPoint);
}

void EnemySubClass::SetRotation() {
	int minRotation = 20;
	int maxRotation = 45;
	this->rotation = rand() % (maxRotation - minRotation) + minRotation;
}

void EnemySubClass::SetSpeed() {
	int minSpeed = 50;
	int maxSpeed = 100;
	this->speed = rand() % (maxSpeed - minSpeed) + minSpeed;
}

void EnemySubClass::SetDirection(int width, int height) {
	float oneDirection = 1.0f;
	//SPAWN on wall UP
	if (this->spawnPoint.y == 0.0f) {
		//Go doww
		this->direction.y = oneDirection;
		//go right or left
		SetDirectionX(width, height);
	}
	//SPAWN on wall DOWN
	else if (this->spawnPoint.y == static_cast<float>(height)) {
		//Go up
		this->direction.y = -oneDirection;
		//go right or left
		SetDirectionX(width, height);
	}
	//SPAWN on wall LEFT
	else if (this->spawnPoint.x == 0.0f) {
		//Go right
		this->direction.x = oneDirection;
		//go up or down
		SetDirectionY(width, height);
	}
	//SPAWN on wall RIGHT
	else if (this->spawnPoint.x == static_cast<float>(width)) {
		//Go left
		this->direction.x = -oneDirection;
		//go up or down
		SetDirectionY(width, height);
	}
}

void EnemySubClass::SetDirectionX(int width, int height) {
	int minX = 1;
	int maxX = 3;
	int rngDirectionX = rand() % (maxX - minX) + minX;
	int rngFactor = rand() % 2;		//0 or 1

	//spawn left -> go right
	if (this->spawnPoint.x < width / 2) {
		this->direction.x = rngDirectionX;
	}
	//spawn right -> go left
	else if (this->spawnPoint.x > width / 2) {
		this->direction.x = -rngDirectionX;
	}
	//spawn middle -> go right or left
	else {
		if (rngFactor) {
			this->direction.x = rngDirectionX;
		}
		else {
			this->direction.x = -rngDirectionX;

		}
	}
}

void EnemySubClass::SetDirectionY(int width, int height) {
	int minY = 1;
	int maxY = 3;
	int rngDirectionY = rand() % (maxY - minY) + minY;
	int rngFactor = rand() % 2;		//0 or 1

	//spawn up -> go down  
	if (this->spawnPoint.y < height / 2) {
		this->direction.y = rngDirectionY;
	}
	//spawn down -> go up
	else if (this->spawnPoint.y > height / 2) {
		this->direction.y = -rngDirectionY;
	}
	//spawn middle -> go up or down
	else {
		if (rngFactor) {
			this->direction.y = rngDirectionY;
		}
		else {
			this->direction.y = -rngDirectionY;
		}
	}
}

void EnemySubClass::SetFollow() {
	int rngFollow = rand() % 101 % 10;		// 1/10 enemy follow player (no counting kamikaze & follow type)

	if (rngFollow == 1) {
		this->isFollowingPlayer = true;
	}
	else {
		this->isFollowingPlayer = false;
	}
}

void EnemySubClass::FollowPlayer(Player* pPlayer, float deltaTime) {
	//pythagore & vector normalization
	float xEnemy = this->shape->getPosition().x;
	float yEnemy = this->shape->getPosition().y;
	float xPlayer = pPlayer->triangle.getPosition().x;
	float yPlayer = pPlayer->triangle.getPosition().y;

	float dx = xPlayer - xEnemy; //difference of x position 
	float dy = yPlayer - yEnemy; // difference of y position 
	float normalizeFactor = sqrt(pow(dx, 2) + pow(dy, 2)); //distance between enemy and player
	Vector2f direction = (pPlayer->triangle.getPosition() - this->shape->getPosition()) / normalizeFactor; //normalize vector
	this->shape->move(direction * speed * deltaTime);
}

void EnemySubClass::LoopOnMap(int width, int height) {
	//down
	if (this->shape->getPosition().x > width) this->shape->setPosition(0.0f, this->shape->getPosition().y);
	//up
	if (this->shape->getPosition().x < 0) this->shape->setPosition((float)width, this->shape->getPosition().y);
	//right
	if (this->shape->getPosition().y > height) this->shape->setPosition(this->shape->getPosition().x, 0.0f);
	//left
	if (this->shape->getPosition().y < 0) this->shape->setPosition(this->shape->getPosition().x, (float)height);
}

#pragma endregion
#pragma region Basic
class Basic : public EnemySubClass {
public:
	//constructor & deconstructor
	Basic();
	~Basic();

	//method
	void SetShape() override;
};

//constructor
Basic::Basic() {
}

//deconstructor
Basic::~Basic() {
}

//method
void Basic::SetShape() {
	int minRadius = 20;
	int maxRadius = 100;
	float rngRadius = static_cast<float>(rand() % (maxRadius - minRadius) + minRadius);
	bool isPolygone = rand() % 2;
	int minPointCount = 12;
	int maxPointCount = 20;
	int rngPointCount = rand() % (maxPointCount - minPointCount) + minPointCount;
	Color color(rand() % 155 + 100,
		rand() % 75,
		rand() % 75);

	this->shape->setRadius(rngRadius);
	this->shape->setOrigin(rngRadius, rngRadius);
	//polygone else circle
	if (isPolygone) {
		this->shape->setPointCount(rngPointCount);
	}
	this->shape->setFillColor(color);

	SetShield();
	SetFollow();
}

#pragma endregion
#pragma region Teleporter
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
	void SetSpeed() override {
		int minSpeed = 50;
		int maxSpeed = 100;
		this->speed = rand() % (maxSpeed - minSpeed) + minSpeed;
		this->saveSpeed = this->speed;
	}
	CircleShape* GetTeleportCircle() override{
		return teleportCircle;
	}
	void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) override {

		this->shape->rotate(deltaAngle * rotation);
		if (isFollowingPlayer == true) {
			FollowPlayer(pPlayer, deltaTime);
		}
		else {
			Move(deltaTime);
		}
		LoopOnMap(width, height);
		this->timeBeforeTeleport -= deltaTime;
		if (this->timeBeforeTeleport <= 0) {
			//get player position
			if (!gotPosition) {
				this->teleportPosition = Vector2f(pPlayer->triangle.getPosition().x, pPlayer->triangle.getPosition().y);
				gotPosition = true;
			}
			//Draw teleportation circle
			this->teleportCircle->setPointCount(5);
			this->teleportCircle->setRadius(this->shape->getRadius());
			this->teleportCircle->setFillColor(tCColor);
			this->teleportCircle->setOutlineThickness(tCRadius);
			this->teleportCircle->setOutlineColor(tCOutline);
			this->teleportCircle->setOrigin(this->teleportCircle->getRadius(), this->teleportCircle->getRadius());
			this->teleportCircle->setPosition(this->teleportPosition);
			//stop move
			this->speed = 0;
			//wait
			this->stopMoveTime -= deltaTime;
			if (this->stopMoveTime <= 0) {
				//teleport
				this->shape->setPosition(this->teleportPosition);
				this->timeBeforeTeleport = 5.0f;
				this->stopMoveTime = 2.0f;
				this->speed = this->saveSpeed;
				this->teleportCircle->setRadius(0);
				this->teleportCircle->setOutlineThickness(0);
				gotPosition = false;
			}
		}
	}
};

//constructor
Teleporter::Teleporter() {
	SetShield();
	SetFollow();
}

//deconstructor
Teleporter::~Teleporter() {
	delete (this->teleportCircle);
}

//method
void Teleporter::SetShape() {
	int minRadius = 50;
	int maxRadius = 80;
	float rngRadius = static_cast<float>(rand() % (maxRadius - minRadius) + minRadius);
	int pointCount = 5;
	Color color(Color::Blue);

	this->shape->setRadius(static_cast<float>(rngRadius));
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(rngRadius, rngRadius);
	this->shape->setFillColor(color);
}
#pragma endregion
#pragma region Kamikaze
class Kamikaze : public EnemySubClass {
public:
	//variable
	float divideNumber = 1.f;
	float timerBeforeExplode = 3.0f;
	float stopMoveTime = 2.0f;

	//constructor & deconstructor
	Kamikaze();
	~Kamikaze();

	//method
	void SetShape() override;
	void SetSpeed() override {
		int minSpeed = 200;
		int maxSpeed = 250;
		this->speed = rand() % (maxSpeed - minSpeed) + minSpeed;
	}
	void SetFollow() override {
		this->isFollowingPlayer = true;
	}
	void SetDivideNumber() {
		float radius = this->shape->getRadius();
		if (radius >= 60) {
			this->divideNumber = 6;
		}
		else if (radius >= 40) {
			this->divideNumber = 3;
		}
	}

	int GetDivideNumber() override {
		return this->divideNumber;
	}

	void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) override {

		this->shape->rotate(deltaAngle * rotation);
		FollowPlayer(pPlayer, deltaTime);
		LoopOnMap(width, height);

		this->timerBeforeExplode -= deltaTime;
		if (this->timerBeforeExplode <= 0) {
			//stop mvt
			this->speed = 0;
			//rotate a lot
			this->rotation = 180;
			//wait
			this->stopMoveTime -= deltaTime;
			if (this->stopMoveTime <= 0) {
				//explode
				this->isAlive = false;
			}
			this->stopMoveTime -= deltaTime;
		}
	}
};

//constructor
Kamikaze::Kamikaze() {
}

//deconstructor
Kamikaze::~Kamikaze() {

}

//method
void Kamikaze::SetShape() {
	int minRadius = 40;
	int maxRadius = 80;
	float rngRadius = static_cast<float>(rand() % (maxRadius - minRadius) + minRadius);
	int pointCount = 6;
	Color color(Color::Magenta);
	float outlineThickness = 5.f;
	Color colorOutline(Color::Red);

	this->shape->setRadius(rngRadius);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(rngRadius, rngRadius);
	this->shape->setFillColor(color);
	this->shape->setOutlineThickness(outlineThickness);
	this->shape->setOutlineColor(colorOutline);

	SetFollow();
	canDivide = true;
	SetDivideNumber();
}

#pragma endregion
#pragma region Mini
class Mini : public EnemySubClass {
public:
	//variable

	//constructor & deconstructor
	Mini();
	~Mini();

	//method
	void SetShape() override;
};

//constructor 
Mini::Mini() {
}

//deconstructor
Mini::~Mini() {
}

//method
void Mini::SetShape() {
	float radius = 10.0f;
	int pointCount = 3;
	Color color(148, 0, 211);	//dark violet
	this->shape->setRadius(radius);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(radius, radius);
	this->shape->setFillColor(color);
}
#pragma endregion
#pragma region Snake
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
	void Move(float deltaTime) override;

};

//constructor 
Snake::Snake() {
	SetShield();
}

//deconstructor
Snake::~Snake() {

}

//method
void Snake::SetShape() {
	int minRadius = 20;
	int maxRadius = 40;
	float rngRadius = static_cast<float>(rand() % (maxRadius - minRadius) + minRadius);
	int minPointCount = 4;
	int maxPointCount = 20;
	int rngPointCount = rand() % (maxPointCount - minPointCount) + minPointCount;
	Color color(rand() % 50, rand() % 255 + 200, rand() % 50);

	this->shape->setRadius(rngRadius);
	this->shape->setPointCount(rngPointCount);
	this->shape->setOrigin(rngRadius, rngRadius);
	this->shape->setFillColor(color);
}

void Snake::Move(float deltaTime) {
	int speedX = 20;
	int speedY = 400;
	int phi = 5;
	this->snakeX--;
	this->snakeY = sin(ConvertDegToRad(this->snakeX * phi));
	this->shape->move(ConvertDegToRad(this->snakeX) * speedX * deltaTime, this->snakeY * speedY * deltaTime);
}
#pragma endregion
#pragma region Tail

class Tail : public EnemySubClass {
public : 
	//variable 

	//constructor & deconstructor
	Tail();
	~Tail();

	//method
	void SetShape() override;
};

//constructor
Tail::Tail() {
}

//deconstructor
Tail::~Tail() {

}

//method
void Tail::SetShape() {
}
#pragma endregion
#pragma region Follower
class Follower : public EnemySubClass {
public:
	//variable

	//constructor & deconstructor
	Follower();
	~Follower();

	//method
	void SetShape() override;
	void SetSpeed() override {
		int minSpeed = 200;
		int maxSpeed = 300;
		this->speed = rand() % (maxSpeed - minSpeed) + minSpeed;
	}
	void SetFollow() override {
		this->isFollowingPlayer = true;
	}
};

//constructor
Follower::Follower() {
	SetShield();
	SetFollow();
}

//deconstructor
Follower::~Follower() {

}

//method
void Follower::SetShape() {
	float radius = 20.0f;
	int pointCount = 4;
	Color color(139, 0, 0);	//fire brick red
	this->shape->setRadius(radius);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(radius, radius);
	this->shape->setFillColor(color);
}
#pragma endregion
#pragma region Divider
class Divider : public EnemySubClass {
public:	
	//variable
	int divideNumber = 0;
	//constructor & deconstructor
	Divider();
	~Divider();

	//method
	void SetShape() override;
	void SetDivideNumber() {
		float radius = this->shape->getRadius();
		if (radius >= 80) {
			this->divideNumber = 9;
		}
		else if (radius >= 60) {
			this->divideNumber = 6;
		}
		else if (radius >= 40) {
			this->divideNumber = 3;
		}
	}

	int GetDivideNumber() override {
		return this->divideNumber;
	}
};

//constructor
Divider::Divider() {
	canDivide = true;
}

//deconstructor
Divider::~Divider() {

}

//method
void Divider::SetShape() {
	int minRadius = 50;
	int maxRadius = 120;
	float rngRadius = static_cast<float>(rand() % (maxRadius - minRadius) + minRadius);
	int pointCount = 6;
	Color color(255, 195, 11);

	this->shape->setRadius(rngRadius);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(rngRadius, rngRadius);
	this->shape->setFillColor(color);

	SetShield();
	SetFollow();
	SetDivideNumber();
}
#pragma endregion
#pragma region Sub
class Sub :public EnemySubClass {
public : 
	//variable
	int life = 1;
	float invicibleTime = 0.2f;
	//constructor & deconstructor
	Sub();
	~Sub();

	//method
	//Setter
	void SetShape(float radius, int pointCount) override;
	void SetSubParameters(float radius, int divideNumber,  Vector2f parentPos, int index) override;
	void SetFollow(EnemyType type) override;
	void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) override{
		this->shape->rotate(deltaAngle * rotation);
		this->invicibleTime -= deltaTime;
		if (isFollowingPlayer == true) {
			FollowPlayer(pPlayer, deltaTime);
		}
		else {
			Move(deltaTime);
		}
		LoopOnMap(width, height);
	}
	
	float GetInvicibleTime() override{
		return this->invicibleTime;
	}

};

//constructor
Sub::Sub() {
}

//deconstructor
Sub::~Sub() {

}

//method
void Sub::SetShape(float radius, int pointCount) {
	Color color(255, 0, 0);

	this->shape->setRadius(radius/ 2);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(radius/ 2, radius/ 2);
	this->shape->setFillColor(color);


}

void Sub::SetSubParameters(float radius, int divideNumber, Vector2f parentPos, int index) {

	float alpha = 360.0f / divideNumber  * index;			//Alpha = 360 degree / (number of enemy to spawn) * index of enemy
	float posX = radius * cos(ConvertDegToRad(alpha));		//Spawn point X = radius * cos(alpha)
	float posY = radius * sin(ConvertDegToRad(alpha));		//Spawn point y = radius * sin(alpha)

	this->spawnPoint = Vector2f(parentPos.x + posX, parentPos.y + posY);
	this->shape->setPosition(this->spawnPoint);
	this->direction = Vector2f(posX, posY);

}

void Sub::SetFollow(EnemyType type) {
	if (type == EnemyType::KAMIKAZE) {
		isFollowingPlayer = true;
		this->speed = 200.0f;
	}
	else {
		isFollowingPlayer = false;
		this->speed = 1.0f;
	}
}
#pragma endregion
#pragma region Lifer
class Lifer : public EnemySubClass {
public :
	//variable

	//constructor & deconstrutor
	Lifer();
	~Lifer();

	//method
	void SetShape() override;
	void SetLife() {
		float radius = this->shape->getRadius();
		if (radius >= 80) {
			this->life = 3;
		}
		else if (radius >= 60) {
			this->life = 2;
		}
	}
};


//constructor
Lifer::Lifer() {
	SetShield();
	SetFollow();
}

//deconstructor
Lifer::~Lifer() {
}

//method
void Lifer::SetShape() {
	int minRadius = 60;
	int maxRadius = 100;
	float rngRadius = static_cast<float>(rand() % (maxRadius - minRadius) + minRadius);
	int pointCount = 7;
	Color color(11, 102, 35);

	this->shape->setRadius(rngRadius);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(rngRadius, rngRadius);
	this->shape->setFillColor(color);

	SetLife();
}
#pragma endregion
#pragma region LifeDivider
class LifeDivider : public EnemySubClass {
public:	
	//variable
	int divideNumber = 0;
	//constructor & deconstructor
	LifeDivider();
	~LifeDivider();
	
	//method
	void SetShape() override;
	void SetDivideNumber() {
		float radius = this->shape->getRadius();
		if (radius >= 80) {
			this->divideNumber = 9;
		}
		else if (radius >= 60) {
			this->divideNumber = 6;
		}
		else if (radius >= 40) {
			this->divideNumber = 3;
		}
	}
	int GetDivideNumber() override {
		return this->divideNumber;
	}

	void SetLife() {
		float radius = this->shape->getRadius();
		if (radius >= 100 ) {
			life = 3;
		}
		else if (radius >= 80) {
			life = 2;
		}
	}

};

//constructor
LifeDivider::LifeDivider() {
	SetShield();
	SetFollow();
	canDivide = true;
}

//deconstrutor
LifeDivider::~LifeDivider() {

}

//method
void LifeDivider::SetShape() {
	int minRadius = 80;
	int maxRadius = 120;
	float rngRadius = static_cast<float>(rand() % (maxRadius - minRadius) + minRadius);
	int pointCount = 8;
	Color color(0, 52, 145);

	this->shape->setRadius(rngRadius);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(rngRadius, rngRadius);
	this->shape->setFillColor(color);

	SetLife();
	SetDivideNumber();
}
#pragma endregion

//INTERFACE
#pragma region Enemy
class Enemy {

public:
	EnemyType type = EnemyType::BASIC;
	EnemySubClass* subClass = nullptr;
	bool isAlive = true;

	//constructor & deconstructor
	Enemy(int width, int height);
	Enemy(int width, int height, EnemyType type);
	Enemy(float radius, int pointCount, int divideNumber, Vector2f parentPos, int index, EnemyType type, EnemyType parentType);
	~Enemy();

	//Method
	//Setter
	void SetType();
	void SetSubClass();
	void SetShape() {
		this->subClass->SetShape();
	}
	void SetShape(float radius, int pointCount) {
		this->subClass->SetShape(radius, pointCount);
	}
	void SetSpawnPoint(int widht, int height) {
		this->subClass->SetSpawnPoint(widht, height);
	}
	void SetSubParameters(float radius, int divideNumber, Vector2f parentPos, int index) {
		this->subClass->SetSubParameters(radius, divideNumber, parentPos, index);
	}
	void SetSpeed() {
		this->subClass->SetSpeed();
	}
	void SetDirection(int width, int height) {
		this->subClass->SetDirection(width, height);
	}

	void SetFollow(EnemyType parentType) {
		this->subClass->SetFollow(parentType);
	}
	void SetHasShield(bool hasShield) {
		this->subClass->hasShield = hasShield;
		this->subClass->shape->setOutlineThickness(0);
	}
	void SetInvicibleTime(float value) {
		this->subClass->invicibleTime = value;
	}
	void UpdateLife() {
		this->subClass->life--;
		this->subClass->shape->setRadius(this->subClass->shape->getRadius() / 2);
		this->subClass->shape->setOrigin(this->subClass->shape->getRadius(), this->subClass->shape->getRadius());
	}
	void UpdateInvicibleTime() {
		this->subClass->invicibleTime--;
	}
	//Getter
	CircleShape GetShape() {
		return *(this->subClass->shape);
	}
	CircleShape GetTeleportCircle() {
		return *(this->subClass->GetTeleportCircle());
	}
	int GetDivideNumber() {
		return this->subClass->GetDivideNumber();
	}
	float GetRadius() {
		return this->subClass->shape->getRadius();
	}
	int GetPointCount() {
		return this->subClass->shape->getPointCount();
	}
	Vector2f GetPosition() {
		return this->subClass->shape->getPosition();
	}
	int GetLife() {
		return this->subClass->GetLife();
	}
	float GetInvicibleTime() {
		return this->subClass->GetInvicibleTime();
	}
	bool GetHasShield() {
		return this->subClass->GetHasShield();
	}
	//update
	void update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) {
		this->subClass->update(width, height, deltaAngle, deltaTime, pPlayer);
		this->isAlive = this->subClass->GetIsAlive();
	}	
};

//CONSTRUCTOR
Enemy::Enemy(int width, int height) {
	SetType();
	SetSubClass();
	SetShape();
	SetSpawnPoint(width, height);
	SetDirection(width, height);
	SetSpeed();
}
Enemy::Enemy(int width, int height, EnemyType type) {
	this->type = type;
	SetSubClass();
	SetShape();
	SetSpawnPoint(width, height);
	SetDirection(width, height);
	SetSpeed();
}

//for type SUB (on divide parent enemy)
Enemy::Enemy(float radius, int pointCount, int divideNumber, Vector2f parentPos, int index, EnemyType type, EnemyType parentType) {
	this->type = type;
	SetSubClass();
	SetShape(radius, pointCount);
	SetSubParameters(radius, divideNumber, parentPos, index);
	SetFollow(parentType);
}
//DESTRUCTOR
Enemy::~Enemy() {
	delete (this->subClass);
}
//METHOD
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
		this->type = EnemyType::BASIC; 
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
		this->type = EnemyType::BASIC;
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
	switch (type)
	{
	case EnemyType::BASIC:
		this->subClass = new Basic;
		break;
	case EnemyType::MINI:
		this->subClass = new Mini;
		break;
	case EnemyType::TELEPORTER:
		this->subClass = new Teleporter;
		break;
	case EnemyType::SNAKE:
		this->subClass = new Snake;
		break;
	case EnemyType::TAIL:
		this->subClass = new Tail;
		break;
	case EnemyType::KAMIKAZE:
		this->subClass = new Kamikaze;
		break;
	case EnemyType::FOLLOWER:
		this->subClass = new Follower;
		break;
	case EnemyType::DIVIDER:
		this->subClass = new Divider;
		break;
	case EnemyType::SUB:
		this->subClass = new Sub;
		break;
	case EnemyType::LIFER:
		this->subClass = new Lifer;
		break;
	case EnemyType::LIFEDIVIDER:
		this->subClass = new LifeDivider;
		break;
	default:
		this->subClass = new Basic;
		break;
	}
}
#pragma endregion

//void EnemyDivide(Enemy* enemy, list<Enemy*>& pEnemyList, int width, int height);
void EnemyDivide(Enemy* pEnemy, list<Enemy*>& pEnemyList) {

	for (int count = 0; count < pEnemy->GetDivideNumber(); count++) {
		Enemy* divide = new Enemy(pEnemy->GetRadius(), pEnemy->GetPointCount(), pEnemy->GetDivideNumber(), pEnemy->GetPosition(), count, EnemyType::SUB, pEnemy->type);
		pEnemyList.push_back(divide);
	}
}
//int EnemySetLife(EnemyType type);
//int EnemySetScoreValue(float radius, EnemyType type);

//TriggerExit
//bool hasCollid = false;
//has collid = true on collision 
// if hit enemy = false
//hasCollide = true && in main has collid = false
//has collidde  =false;
//