#include "Enemy.h"
#include "ScreenResolution.h"

string EnemySetShapeType() {
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
	int rngShape = rand() % shapeVect.size();
	return shapeVect[rngShape];
}

Vector2f EnemySetSpawnPoint(int width, int height) {

	float rngWidth = static_cast<float>(rand() % width);
	float rngHeight = static_cast<float>(rand() % height);
	int rngWallSpawn = rand() % 4 + 1;
	Vector2f spawnPoint = Vector2f(0, 0);
		
	//UP
	if (rngWallSpawn == 1) {
		spawnPoint = Vector2f(rngWidth, 0);
	}
	//RIGHT
	else if (rngWallSpawn == 2) {
		spawnPoint = Vector2f((float)width, rngHeight);
	}
	//DOWN
	else if (rngWallSpawn == 3) {
		spawnPoint = Vector2f(rngWidth, (float)height);
	}
	//LEFT
	else if (rngWallSpawn == 4) {
		spawnPoint = Vector2f(0, rngHeight);
	}
	return spawnPoint;
}

Color EnemySetColor() {

	int rngColor = rand() % 5 + 1;
	Color color(rand() % 155 + 100,
		rand() % 75,
		rand() % 75,
		255);
	//Color color;
	//color = Color::Red;

	//if (rngColor == 1) {
	//	color = Color::Yellow;
	//}
	//else if (rngColor == 2) {
	//	color = Color::Red;
	//}
	//else if (rngColor == 3) {
	//	color = Color::Green;
	//}
	//else if (rngColor == 4) {
	//	color = Color::Blue;
	//}
	//else if (rngColor == 5) {
	//	color = Color::Magenta;
	//}

	return color;
}


void EnemySetShape(Enemy* pEnemy, CircleShape* pShape) {

	int rngPointCount = rand() % 10 + 10;

	if (pEnemy->shapeType == "Square") {
		pShape->setPointCount(4);
	}
	else if (pEnemy->shapeType == "Pentagon") {
		pShape->setPointCount(5);
	}
	else if (pEnemy->shapeType == "Hexagon") {
		pShape->setPointCount(6);
	}
	else if (pEnemy->shapeType == "Heptagon") {
		pShape->setPointCount(7);
	}
	else if (pEnemy->shapeType == "Octagon") {
		pShape->setPointCount(8);
	}
	else if (pEnemy->shapeType == "Enneagone") {
		pShape->setPointCount(9);
	}
	else if (pEnemy->shapeType == "Decagone") {
		pShape->setPointCount(10);
	}
	else if (pEnemy->shapeType == "Polygon") {
		pShape->setPointCount(rngPointCount);
	}

	pShape->setRadius(pEnemy->radius);
	pShape->setOrigin(pEnemy->radius, pEnemy->radius);
	pShape->setPosition(pEnemy->spawnPoint);
	pShape->setFillColor(pEnemy->color);
}
int EnemySetAngle() {
	int rngAngle = rand() % 60;
	return rngAngle;
}

float EnemySetRadius() {
	float rngRadius = static_cast<float>(rand() % 50 + 10);
	return rngRadius;
}
int EnemySetSpeed() {
	int rngSpeed = rand() % 200 + 100;
	return rngSpeed;
}

int EnemySetRotation() {
	int rngRotation = rand() % 45 + 10;
	return rngRotation;
}

Vector2f EnemySetVelocity(float x, float y, int width, int height, float speed) {
	Vector2f velocity;
	int rngSpeed = rand() % 100 + 100;
	int rngDirection = rand() % 2;
	// + x decale droite
	// - x decale gauche
	//height 0 UP WALL
	//x < width / 2 == full left
	//x == width/2 == middle
	//x > width / 2 == full right
	//
	// + y descend
	// - y monte
	//y < height / 2 == full up
	//y == height / 2 == middle 
	//y > height / 2 == full down
	//height /2 
	//width /2

	//up wall
	if (y == 0.0f) {
		//left
		if (rngDirection != 0) {
			if (x < width / 2) {
				velocity = Vector2f(rngSpeed, speed);
			}
			//middle
			else if (x == width / 2) {
				if (rngDirection == 1) {
					velocity = Vector2f(rngSpeed, speed);
				}
				else{
					velocity = Vector2f(-rngSpeed, speed);
				}
			}
			//right
			else if (x > width / 2) {
				velocity = Vector2f(-rngSpeed, speed);
			}
		}
		else {
			velocity = Vector2f(0.0f, speed);
		}

		
	}
	// down wall
	else if (y == height) {
		if (rngDirection != 0) {
			if (x < width / 2) {
				velocity = Vector2f(rngSpeed, -speed);
			}
			//middle
			else if (x == width / 2) {
				if (rngDirection == 1) {
					velocity = Vector2f(rngSpeed, -speed);
				}
				else {
					velocity = Vector2f(-rngSpeed, -speed);
				}
			}
			//right
			else if (x > width / 2) {
				velocity = Vector2f(-rngSpeed, -speed);
			}
		}
		else {
			velocity = Vector2f(0.0f, -speed);
		}
		
	}
	//left wall
	else if (x == 0.0f) {
		//up
		if (rngDirection != 0) {
			if (y < height / 2) {
				velocity = Vector2f(speed, rngSpeed);
			}
			//middle
			else if (y == height / 2) {
				if (rngDirection == 1) {
					velocity = Vector2f(speed, rngSpeed);
				}
				else {
					velocity = Vector2f(speed, -rngSpeed);
				}
			}
			//downs
			else if (y > height / 2) {
				velocity = Vector2f(speed, -rngSpeed);
			}
		}
		else {
			velocity = Vector2f(speed, 0.0f);
		}
		
	}
	//right wall
	else if (x == width) {
		if (rngDirection != 0) {
			//up
			if (y < height / 2) {
				velocity = Vector2f(-speed, rngSpeed);
			}
			//middle
			else if (y == height / 2) {
				if (rngDirection == 1) {
					velocity = Vector2f(-speed, rngSpeed);
				}
				else {
					velocity = Vector2f(-speed, -rngSpeed);
				}
			}
			//downs
			else if (y > height / 2) {
				velocity = Vector2f(-speed, -rngSpeed);
			}

		}
		else {
			velocity = Vector2f(-speed, 0.0f);
		}
	}

	return velocity;
}

int EnemySetLife() {
	int rngLife = rand()%3 +1;
	return rngLife;
}

int EnemySetSize(float radius) {
	int size = 1;

	if (radius > 50) {
		size = 3;
	}
	else if (radius > 30) {
		size = 2;
	}
	return size;
}

int EnemySetScoreValue(float radius) {
	int scoreVal = (int)radius * 10;
	return scoreVal;
}

Enemy* EnemyCreate(int width, int height) {
	Enemy* enemy = new Enemy;
	CircleShape shape;

	//Shape
	enemy->shapeType = EnemySetShapeType();
	enemy->spawnPoint = EnemySetSpawnPoint(width, height);
	enemy->color = EnemySetColor();
	enemy->angle = EnemySetAngle();
	enemy->radius = EnemySetRadius();
	EnemySetShape(enemy, &shape);
	enemy->shape = shape;

	//Speed
	enemy->speed = EnemySetSpeed();
	enemy->rotation = EnemySetRotation();
	enemy->velocity = EnemySetVelocity(enemy->spawnPoint.x, enemy->spawnPoint.y, width, height, enemy->speed);

	//bool
	enemy->isAlive = true;
	enemy->hasSpawn = false;

	//Gameplay & UI
	enemy->life = EnemySetLife();
	enemy->size = EnemySetSize(enemy->radius);
	enemy->scoreValue = EnemySetScoreValue(enemy->radius);
	return enemy;
}

void EnemyUpdate(Enemy* pEnemy, int width, int height, float deltaTime, float deltaAngle) {
	//Move Enemy
	pEnemy->shape.setPosition(pEnemy->shape.getPosition() + pEnemy->velocity * deltaTime);
	pEnemy->shape.rotate(deltaAngle);
	//loop map
	//down
	if (pEnemy->shape.getPosition().x > width) pEnemy->shape.setPosition(0.0f, pEnemy->shape.getPosition().y);
	//up
	if (pEnemy->shape.getPosition().x < 0) pEnemy->shape.setPosition((float)width, pEnemy->shape.getPosition().y);
	//right
	if (pEnemy->shape.getPosition().y > height) pEnemy->shape.setPosition(pEnemy->shape.getPosition().x, 0.0f);
	//left
	if (pEnemy->shape.getPosition().y < 0) pEnemy->shape.setPosition(pEnemy->shape.getPosition().x, (float)height);
}

void EnemyDestroy(Enemy* pEnemy){
	delete pEnemy;
}