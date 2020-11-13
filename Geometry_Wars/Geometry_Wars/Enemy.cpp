#include "Enemy.h"
#include "ScreenResolution.h"

float M_PI = 3.141592653;

string EnemySetShapeType() {
	#pragma region Shape
	vector<string> shapeVect{
		"Circle",
		"Square",
		"Pentagon",
		"Hexagon",
		"Heptagon",
		"Octagon",
		"Enneagone",
		"Decagone",
		"Polygon"
	};
	#pragma endregion
	int rngShape = rand() % shapeVect.size();
	return shapeVect[rngShape];
}

Vector2f EnemySetSpawnPoint(int width, int height) {

	int rngWidth = rand() % width;
	int rngHeight = rand() % height;
	int rngWallSpawn = rand() % 4 + 1;
	Vector2f spawnPoint = Vector2f(0, 0);
		
	//UP
	if (rngWallSpawn == 1) {
		spawnPoint = Vector2f(rngWidth, 0);
	}
	//RIGHT
	else if (rngWallSpawn == 2) {
		spawnPoint = Vector2f(width, rngHeight);
	}
	//DOWN
	else if (rngWallSpawn == 3) {
		spawnPoint = Vector2f(rngWidth, height);
	}
	//LEFT
	else if (rngWallSpawn == 4) {
		spawnPoint = Vector2f(0, rngHeight);
	}
	return spawnPoint;
}

Color EnemySetColor() {

	int rngColor = rand() % 5 + 1;
	Color color;
	color = Color::Red;

	if (rngColor == 1) {
		color = Color::Yellow;
	}
	else if (rngColor == 2) {
		color = Color::Red;
	}
	else if (rngColor == 3) {
		color = Color::Green;
	}
	else if (rngColor == 4) {
		color = Color::Blue;
	}
	else if (rngColor == 5) {
		color = Color::Magenta;
	}

	return color;
}

float EnemySetSpeed() {
	float rngSpeed = static_cast <float> (rand()) / (static_cast<float> (RAND_MAX/0.5f));

	return rngSpeed;
}

float EnemySetRotationSpeed() {
	float rngRotation = static_cast <float> (rand()) / (static_cast<float> (RAND_MAX));
	return rngRotation;
}

float EnemySetAngle(float w, float h, float width, float height) {
	float rngAngle = rand() % 45;
	return rngAngle;
}

Vector2f EnemySetVelocity(float w, float h, float width, float height, float speed) {
	Vector2f velocity;

	//up wall
	if (h == 0) {
		velocity = Vector2f(0, speed);
	}
	// down wall
	else if (h == height) {
		velocity = Vector2f(0, -speed);
	}
	//left wall
	else if (w == 0) {
		velocity = Vector2f(speed, 0);
	}
	//right wall
	else if (w == width) {
		velocity = Vector2f(-speed, 0);
	}

	return velocity;
}

int EnemySetRadius() {
	int rngRadius = rand() % 50 + 10;
	return rngRadius;
}



Enemy EnemyCreate(int width, int height) {
	
//
	Enemy enemy;
	enemy.shapeType = EnemySetShapeType();
	enemy.spawnPoint = EnemySetSpawnPoint(width, height);
	enemy.color = EnemySetColor();
	enemy.speed = EnemySetSpeed();
	enemy.rotationSpeed = EnemySetRotationSpeed();
	enemy.angle = EnemySetAngle(enemy.spawnPoint.x, enemy.spawnPoint.y, width, height);
	enemy.radius = EnemySetRadius();
	enemy.velocity = EnemySetVelocity(enemy.spawnPoint.x, enemy.spawnPoint.y, width, height, enemy.speed);
	enemy.hasSpawn = false;
	return enemy;
}

CircleShape CreateEnemyShape(Enemy enemy) {

	int rngVertex = rand() % 20 + 10;
	CircleShape shape(enemy.radius);

	if (enemy.shapeType == "Circle") {
		CircleShape shape(enemy.radius);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	else if (enemy.shapeType == "Square") {
		CircleShape shape(enemy.radius, 4);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	else if (enemy.shapeType == "Pentagon") {
		CircleShape shape(enemy.radius, 5);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	else if (enemy.shapeType == "Hexagon") {
		CircleShape shape(enemy.radius, 6);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	else if (enemy.shapeType == "Heptagon") {
		CircleShape shape(enemy.radius, 7);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	else if (enemy.shapeType == "Octagon") {
		CircleShape shape(enemy.radius, 8);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	else if (enemy.shapeType == "Enneagone") {
		CircleShape shape(enemy.radius, 9);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	else if (enemy.shapeType == "Decagone") {
		CircleShape shape(enemy.radius, 10);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	else if (enemy.shapeType == "Polygon") {
		CircleShape shape(enemy.radius, rngVertex);
		shape.setOrigin(enemy.radius, enemy.radius);
		shape.setPosition(enemy.spawnPoint);
		shape.setFillColor(enemy.color);
		return shape;
	}
	shape.setOrigin(enemy.radius, enemy.radius);
	shape.setPosition(enemy.spawnPoint);
	shape.setFillColor(enemy.color);
	return shape;
}

void EnemyUpdatePosition() {

}

void EnemySetForme(Enemy* enemy, CircleShape* shape) {

	int rngPointCount = rand() % 10 + 10;

	if (enemy->shapeType == "Square") {
		shape->setPointCount(4);
	}
	else if (enemy->shapeType == "Pentagon") {
		shape->setPointCount(5);
	}
	else if (enemy->shapeType == "Hexagon") {
		shape->setPointCount(6);
	}
	else if (enemy->shapeType == "Heptagon") {
		shape->setPointCount(7);
	}
	else if (enemy->shapeType == "Octagon") {
		shape->setPointCount(8);
	}
	else if (enemy->shapeType == "Enneagone") {
		shape->setPointCount(9);
	}
	else if (enemy->shapeType == "Decagone") {
		shape->setPointCount(10);
	}
	else if (enemy->shapeType == "Polygon") {
		shape->setPointCount(rngPointCount);
	}

	shape->setRadius(enemy->radius);
	shape->setOrigin(enemy->radius, enemy->radius);
	shape->setPosition(enemy->spawnPoint);
	shape->setFillColor(enemy->color);
}

Enemy* EnemyDCreate(int width, int height) {
	Enemy* enemy = new Enemy;
	CircleShape forme;

	enemy->shapeType = EnemySetShapeType();
	enemy->spawnPoint = EnemySetSpawnPoint(width, height);
	enemy->color = EnemySetColor();
	enemy->speed = EnemySetSpeed();
	enemy->rotationSpeed = EnemySetRotationSpeed();
	enemy->angle = EnemySetAngle(enemy->spawnPoint.x, enemy->spawnPoint.y, width, height);
	enemy->radius = EnemySetRadius();
	enemy->velocity = EnemySetVelocity(enemy->spawnPoint.x, enemy->spawnPoint.y, width, height, enemy->speed);
	enemy->hasSpawn = false;
	EnemySetForme(enemy, &forme);
	enemy->shape = forme;

	return enemy;
}

void EnemyDestroy(Enemy* pEnemy){
	delete pEnemy;
}