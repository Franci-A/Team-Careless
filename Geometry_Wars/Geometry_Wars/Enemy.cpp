#include "Enemy.h"
#include "ScreenResolution.h"

float M_PI = 3.141592653;

CircleShape ShapeDraw() {
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
	int rngRadius = rand() % 50 + 10;
	int rngShape = rand() % (shapeVect.size() - 1);
	int rngVertex = rand() % 20 + 10;
	CircleShape shape;

	if (shapeVect[rngShape] == "Circle") {
		CircleShape shape(rngRadius);
	}
	else if (shapeVect[rngShape] == "Square") {
		CircleShape shape(rngRadius, 4);
	}
	else if (shapeVect[rngShape] == "Pentagon") {
		CircleShape shape(rngRadius, 5);
	}
	else if (shapeVect[rngShape] == "Hexagon") {
		CircleShape shape(rngRadius, 6);
	}
	else if (shapeVect[rngShape] == "Heptagon") {
		CircleShape shape(rngRadius, 7);
	}
	else if (shapeVect[rngShape] == "Octagon") {
		CircleShape shape(rngRadius, 8);
	}
	else if (shapeVect[rngShape] == "Enneagone") {
		CircleShape shape(rngRadius, 9);
	}
	else if (shapeVect[rngShape] == "Decagone") {
		CircleShape shape(rngRadius, 10);
	}
	else if (shapeVect[rngShape] == "Polygone") {
		CircleShape shape(rngRadius, rngVertex);
	}

	return shape;
}

Vector2f ShapeSetSpawnPoint(int width, int height) {

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

Color ShapeSetColor() {

	int rngColor = rand() % 7 + 1;
	Color color;
	color.White;

	if (rngColor == 1) {
		color.White;
	}
	else if (rngColor == 2) {
		color.Red;
	}
	else if (rngColor == 3) {
		color.Green;
	}
	else if (rngColor == 4) {
		color.Blue;
	}
	else if (rngColor == 5) {
		color.Yellow;
	}
	else if (rngColor == 6) {
		color.Cyan;
	}
	else if (rngColor == 7) {
		color.Magenta;
	}

	return color;
}

CircleShape ShapeCreate(int width, int height) {
	CircleShape shape;
	shape = ShapeDraw();
	shape.setPosition(ShapeSetSpawnPoint(width, height));
	shape.setFillColor(ShapeSetColor());
	return shape;
}

void EnemySetPosition() {

}

void EnemySetSpeed() {
	int rngSpeedLimit = rand() % 10 + 1;
	float rngSpeed = (float)rngSpeedLimit * 0.1;
}

void EnemySetRotationSpeed() {
	int rngRotation = rand() % 45 + 10;
}

void EnemySetAngle() {
	float rngAngle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f * M_PI)));
}

Enemy EnemyCreate(int width, int height) {

	Enemy enemy;
	CircleShape shape = ShapeCreate(width, height);
	enemy.SetShape(shape);
	EnemySetSpeed();
	EnemySetRotationSpeed();
	EnemySetAngle();

	return enemy;
}