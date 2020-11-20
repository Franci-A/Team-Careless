#include "EnemyClass.h"

#pragma region Constructor

EnemySubClass::EnemySubClass() { SetRotation(); }
Basic::Basic() {}
Teleporter::Teleporter() {}
Kamikaze::Kamikaze() {}
Mini::Mini() {}
Snake::Snake() {}
Tail::Tail() {}
Follower::Follower() {}
Divider::Divider() {}
Sub::Sub() {}
Lifer::Lifer() {}
LifeDivider::LifeDivider() {}
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
	//type SUB (on divide parent enemy)
Enemy::Enemy(float radius, int pointCount, int divideNumber, Vector2f parentPos, int index, EnemyType type, EnemyType parentType) {
	this->type = type;
	SetSubClass();
	SetShape(radius, pointCount);
	SetSubParameters(radius, divideNumber, parentPos, index);
	SetFollow(parentType);
}
	//type lifeDivider
Enemy::Enemy(Enemy* pEnemy, int index) {
	if (pEnemy->GetLife() == 3) {
		this->type = EnemyType::LIFEDIVIDER;
		SetSubClass();
		SetShape(pEnemy->GetRadius(), pEnemy->GetPointCount(), pEnemy->GetLife(), index, pEnemy->GetPosition());
	}
	else if (pEnemy->GetLife() == 2) {
		this->type = EnemyType::SUB;
		SetSubClass();
		SetShape(pEnemy->GetRadius(), pEnemy->GetPointCount());
		SetSubParameters(pEnemy->GetRadius(), 1, pEnemy->GetPosition(), 1);
		SetFollow(pEnemy->type);
	}
}

#pragma endregion
#pragma region Deconstructor
EnemySubClass::~EnemySubClass() { delete shape; }
Basic::~Basic() {}
Teleporter::~Teleporter() { delete (this->teleportCircle); }
Kamikaze::~Kamikaze() {}
Mini::~Mini() {}
Snake::~Snake() {}
Tail::~Tail() {}
Follower::~Follower() {}
Divider::~Divider() {}
Sub::~Sub() {}
Lifer::~Lifer() {}
LifeDivider::~LifeDivider() {}
Enemy::~Enemy() { delete (this->subClass); }
#pragma endregion
#pragma region Method
#pragma region Method EnemySubClass
#pragma region Setter
void EnemySubClass::SetShape() {
	this->shape->setRadius(50);
	this->shape->setOrigin(shape->getRadius(), shape->getRadius());
	this->shape->setFillColor(Color::Red);
}
void EnemySubClass::SetShape(float radius, int pointCount) {}
void EnemySubClass::SetShape(float radius, int pointCount, int life, int index, Vector2f parentPos){}
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
void EnemySubClass::SetSubParameters(float radius, int divideNumber, Vector2f parentPos, int index) {}
void EnemySubClass::SetFollow(EnemyType type) {}
void EnemySubClass::SetInvicibleTime(float value) { this->invicibleTime = value; }
#pragma endregion
#pragma region Getter
int EnemySubClass::GetLife() { return this->life; }
bool EnemySubClass::GetIsAlive() { return this->isAlive; }
float EnemySubClass::GetInvicibleTime() { return this->invicibleTime; }
bool EnemySubClass::GetHasShield() { return this->hasShield; }
bool EnemySubClass::GetHasExplode() { return this->hasExplode; }
CircleShape* EnemySubClass::GetTeleportCircle() { return nullptr; }
int EnemySubClass::GetDivideNumber() { return this->divideNumber; }
#pragma endregion
#pragma region Update
void EnemySubClass::Move(float deltaTime) {
	this->shape->move(this->direction * this->speed * deltaTime);
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
void EnemySubClass::update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) {

	this->shape->rotate(deltaAngle * rotation);
	if (isFollowingPlayer == true) {
		FollowPlayer(pPlayer, deltaTime);
	}
	else {
		Move(deltaTime);
	}
	LoopOnMap(width, height);
}
#pragma endregion
#pragma endregion EnemySubClass
#pragma region Method Basic 
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
	//polygone shape else circle
	if (isPolygone) {
		this->shape->setPointCount(rngPointCount);
	}
	this->shape->setFillColor(color);

	SetShield();
	SetFollow();
}
#pragma endregion Basic
#pragma region Method Teleporter
#pragma region Setter
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

	SetShield();
	SetFollow();
}

void Teleporter::SetSpeed() {
	int minSpeed = 50;
	int maxSpeed = 100;
	this->speed = rand() % (maxSpeed - minSpeed) + minSpeed;
	this->saveSpeed = this->speed;
}

#pragma endregion
#pragma region Getter
CircleShape* Teleporter::GetTeleportCircle() { return teleportCircle; }
#pragma endregion
#pragma region Update
void Teleporter::update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) {
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
#pragma endregion
#pragma endregion Teleporter
#pragma region Method Kamikaze
#pragma region Setter
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
void Kamikaze::SetSpeed() {
	int minSpeed = 200;
	int maxSpeed = 250;
	this->speed = rand() % (maxSpeed - minSpeed) + minSpeed;
}
void Kamikaze::SetFollow() { 
	this->isFollowingPlayer = true; 
}
void Kamikaze::SetDivideNumber() {
	float radius = this->shape->getRadius();
	if (radius >= 60) {
		this->divideNumber = 6;
	}
	else if (radius >= 40) {
		this->divideNumber = 3;
	}
}
#pragma endregion 
#pragma region Update
void Kamikaze::update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) {
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
			this->hasExplode = true;
		}
		this->stopMoveTime -= deltaTime;
	}
}
#pragma endregion
#pragma endregion Kamikaze
#pragma region Method Mini
void Mini::SetShape() {
	float radius = 10.0f;
	int pointCount = 3;
	Color color(148, 0, 211);	//dark violet
	this->shape->setRadius(radius);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(radius, radius);
	this->shape->setFillColor(color);
}
#pragma endregion Mini
#pragma region Method Snake
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

	SetShield();
}

void Snake::Move(float deltaTime) {
	int speedX = 20;
	int speedY = 400;
	int phi = 5;
	this->snakeX--;
	this->snakeY = sin(ConvertDegToRad(this->snakeX * phi));
	this->shape->move(ConvertDegToRad(this->snakeX) * speedX * deltaTime, this->snakeY * speedY * deltaTime);
}
#pragma endregion Snake
#pragma region Method Tail
void Tail::SetShape() {}
#pragma endregion Tail
#pragma region Method Follower
void Follower::SetShape() {
	float radius = 40.0f;
	int pointCount = 4;
	Color color(139, 0, 0);	//fire brick red
	this->shape->setRadius(radius);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(radius, radius);
	this->shape->setFillColor(color);
	this->shape->setScale(1, .5f);
	SetShield();
	SetFollow();
}

void Follower::SetSpeed() {
	int minSpeed = 200;
	int maxSpeed = 300;
	this->speed = rand() % (maxSpeed - minSpeed) + minSpeed;
}

void Follower::SetFollow() {
	this->isFollowingPlayer = true;
}
#pragma endregion Follower
#pragma region Method Divider
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

	canDivide = true;
	SetShield();
	SetFollow();
	SetDivideNumber();
}
void Divider::SetDivideNumber() {
	float radius = this->shape->getRadius();
	/*		if (radius >= 80) {
				this->divideNumber = 9;
			}
			else */if (radius >= 60) {
				this->divideNumber = 6;
			}
			else if (radius >= 40) {
				this->divideNumber = 3;
			}
}
#pragma endregion Divider
#pragma region Method Sub
#pragma region Setter
void Sub::SetShape(float radius, int pointCount) {
	Color color(255, 0, 0);

	this->shape->setRadius(radius / 2);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(radius / 2, radius / 2);
	this->shape->setFillColor(color);

}

void Sub::SetSubParameters(float radius, int divideNumber, Vector2f parentPos, int index) {

	float alpha = 360.0f / divideNumber * index;			//Alpha = 360 degree / (number of enemy to spawn) * index of enemy
	float posX = radius * cos(ConvertDegToRad(alpha));		//Spawn point X = radius * cos(alpha)
	float posY = radius * sin(ConvertDegToRad(alpha));		//Spawn point y = radius * sin(alpha)

	this->spawnPoint = Vector2f(parentPos.x + posX, parentPos.y + posY);
	this->shape->setPosition(this->spawnPoint);
	this->direction = Vector2f(posX, posY);

	this->life = 1;
	this->invicibleTime = 0.2f;
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
#pragma region Update
void Sub::update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer)
{
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
#pragma endregion
#pragma endregion Sub
#pragma region Method Lifer
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

	int minSpeed = 50;
	int maxSpeed = 100;
	this->speed = static_cast<float>(rand() % (maxSpeed - minSpeed) + minSpeed);
	SetShield();
	SetFollow();
	SetLife();
}
void Lifer::SetLife() {
	float radius = this->shape->getRadius();
	if (radius >= 80) {
		this->life = 3;
	}
	else if (radius >= 60) {
		this->life = 2;
	}
}
#pragma endregion Lifer
#pragma region Method LifeDivider
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

	canDivide = true;
	SetShield();
	SetFollow();
	SetLife();
}

void LifeDivider::SetShape(float radius, int pointCount, int life, int index, Vector2f parentPos) {
	Color color(0, 52, 145);
	this->shape->setRadius(radius / 2);
	this->shape->setPointCount(pointCount);
	this->shape->setOrigin(radius / 2, radius / 2);
	this->shape->setFillColor(color);
	this->life = life - 1;
	this->divideNumber = 2;

	float alpha = 360.0f / divideNumber * index;			//Alpha = 360 degree / (number of enemy to spawn) * index of enemy
	float posX = radius * cos(ConvertDegToRad(alpha));		//Spawn point X = radius * cos(alpha)
	float posY = radius * sin(ConvertDegToRad(alpha));		//Spawn point y = radius * sin(alpha)

	this->spawnPoint = Vector2f(parentPos.x + posX, parentPos.y + posY);
	this->shape->setPosition(this->spawnPoint);
	this->direction = Vector2f(posX, posY);

	this->life = 1;
	this->invicibleTime = 0.2f;
	this->speed = 1.0f;
}
void LifeDivider::SetDivideNumber() {
	float radius = this->shape->getRadius();
	/*		if (radius >= 80) {
				this->divideNumber = 9;
			}
			else */if (radius >= 60) {
				this->divideNumber = 6;
			}
			else if (radius >= 40) {
				this->divideNumber = 3;
			}
}
void LifeDivider::SetLife() {
	//float radius = this->shape->getRadius();
	this->life = 3;
}
#pragma endregion LifeDivider
#pragma region Method Enemy
#pragma region Setter
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
void Enemy::SetShape() { this->subClass->SetShape(); }
void Enemy::SetShape(float radius, int pointCount) { this->subClass->SetShape(radius, pointCount); }
void Enemy::SetShape(float radius, int pointCount, int life, int index, Vector2f parentPos) { this->subClass->SetShape(radius, pointCount, life, index, parentPos); }
void Enemy::SetSpawnPoint(int widht, int height) { this->subClass->SetSpawnPoint(widht, height); }
void Enemy::SetSubParameters(float radius, int divideNumber, Vector2f parentPos, int index) { this->subClass->SetSubParameters(radius, divideNumber, parentPos, index); }
void Enemy::SetSpeed() { this->subClass->SetSpeed(); }
void Enemy::SetDirection(int width, int height) { this->subClass->SetDirection(width, height); }
void Enemy::SetFollow(EnemyType parentType) { this->subClass->SetFollow(parentType); }
void Enemy::SetInvicibleTime(float value) { this->subClass->SetInvicibleTime(value); }
#pragma endregion
#pragma region Getter
CircleShape Enemy::GetShape() { return *(this->subClass->shape); }
CircleShape Enemy::GetTeleportCircle() { return *(this->subClass->GetTeleportCircle()); }
int Enemy::GetDivideNumber() { return this->subClass->GetDivideNumber(); }
float Enemy::GetRadius() { return this->subClass->shape->getRadius(); }
int Enemy::GetPointCount() { return this->subClass->shape->getPointCount(); }
Vector2f Enemy::GetPosition() { return this->subClass->shape->getPosition(); }
int Enemy::GetLife() { return this->subClass->GetLife(); }
float  Enemy::GetInvicibleTime() { return this->subClass->GetInvicibleTime(); }
bool Enemy::GetHasExplode() { return this->subClass->GetHasExplode(); }
bool Enemy::GetHasShield() { return this->subClass->GetHasShield(); }
#pragma endregion
#pragma region Update
void Enemy::UpdateHasShield() {
	this->subClass->hasShield = false;
	this->subClass->shape->setOutlineThickness(0);
}
void Enemy::UpdateLife() {
	this->subClass->life--;
	this->subClass->shape->setRadius(this->subClass->shape->getRadius() / 2);
	this->subClass->shape->setOrigin(this->subClass->shape->getRadius(), this->subClass->shape->getRadius());
}
void Enemy::UpdateInvicibleTime(float deltaTime) {
	this->subClass->invicibleTime -= deltaTime;
}
void Enemy::update(int width, int height, float deltaAngle, float deltaTime, Player* pPlayer) {
	this->subClass->update(width, height, deltaAngle, deltaTime, pPlayer);
	this->isAlive = this->subClass->GetIsAlive();
}
#pragma endregion 
#pragma endregion Enemy
#pragma endregion Method