#include "Enemy.h"
#include "ScreenResolution.h"

float M_PI = 3.141592653;

string EnemySetShape() {
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
	int rngShape = rand() % (shapeVect.size() - 1);
	return shapeVect[rngShape];
}

int EnemySetRadius() {
	int rngRadius = rand() % 50 + 10;
	return rngRadius;
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

	int rngColor = rand() % 7 + 1;
	Color color;
	color = Color::White;

	if (rngColor == 1) {
		color = Color::White;
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
	else if (rngColor == 6) {
		color = Color::Cyan;
	}
	else if (rngColor == 7) {
		color = Color::Yellow;
	}

	return color;
}

float EnemySetSpeed() {
	int rngSpeedLimit = rand() % 10 + 1;
	float rngSpeed = (float)rngSpeedLimit * 0.1;

	return rngSpeed;
}

float EnemySetRotationSpeed() {
	int rngRotation = rand() % 45 + 10;
	return rngRotation;
}

float EnemySetAngle() {
	float rngAngle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f * M_PI)));
	return rngAngle;
}

Enemy EnemyCreate(int width, int height) {

	Enemy enemy;
	enemy.shape = EnemySetShape();
	enemy.spawnPoint = EnemySetSpawnPoint(width, height);
	enemy.color = EnemySetColor();
	enemy.speed = EnemySetSpeed();
	enemy.rotationSpeed = EnemySetRotationSpeed();
	enemy.angle = EnemySetAngle();
	enemy.radius = EnemySetRadius();
	return enemy;
}

CircleShape CreateEnemyShape(Enemy enemy) {

	int rngVertex = rand() % 20 + 10;
	CircleShape shape(enemy.radius);

	if (enemy.shape == "Circle") {
		CircleShape shape(enemy.radius);
	}
	else if (enemy.shape == "Square") {
		CircleShape shape(enemy.radius, 4);
	}
	else if (enemy.shape == "Pentagon") {
		CircleShape shape(enemy.radius, 5);
	}
	else if (enemy.shape == "Hexagon") {
		CircleShape shape(enemy.radius, 6);
	}
	else if (enemy.shape == "Heptagon") {
		CircleShape shape(enemy.radius, 7);
	}
	else if (enemy.shape == "Octagon") {
		CircleShape shape(enemy.radius, 8);
	}
	else if (enemy.shape == "Enneagone") {
		CircleShape shape(enemy.radius, 9);
	}
	else if (enemy.shape == "Decagone") {
		CircleShape shape(enemy.radius, 10);
	}
	else if (enemy.shape == "Polygone") {
		CircleShape shape(enemy.radius, rngVertex);
	}

	shape.setPosition(enemy.spawnPoint);
	shape.setFillColor(enemy.color);
	shape.setOrigin(enemy.radius, enemy.radius);
	return shape;
}
void EnemyUpdatePosition() {

}