//#include "Enemy.h"
//#include "PlayerController.h"
//#include "MathUtils.h"
//
//string EnemySetShapeType() {
//	vector<string> shapeVect{
//		"Circle",
//		"Square",
//		"Pentagon",
//		"Hexagon",
//		"Heptagon",
//		"Octagon",
//		"Enneagone",
//		"Decagone",
//		"Polygon"
//	};
//	int rngShape = rand() % shapeVect.size();
//	return shapeVect[rngShape];
//}
//
//Vector2f EnemySetSpawnPoint(int width, int height, EnemyType type) {
//
//	float rngWidth = static_cast<float>(rand() % width);
//	float rngHeight = static_cast<float>(rand() % height);
//	int rngWallSpawn = rand() % 4 + 1;
//	Vector2f spawnPoint = Vector2f(0, 0);
//
//	if (type != EnemyType::SNAKE) {
//		//UP
//		if (rngWallSpawn == 1) {
//			spawnPoint = Vector2f(rngWidth, 0);
//		}
//		//RIGHT
//		else if (rngWallSpawn == 2) {
//			spawnPoint = Vector2f((float)width, rngHeight);
//		}
//		//DOWN
//		else if (rngWallSpawn == 3) {
//			spawnPoint = Vector2f(rngWidth, (float)height);
//		}
//		//LEFT
//		else if (rngWallSpawn == 4) {
//			spawnPoint = Vector2f(0, rngHeight);
//		}
//	}
//	else {
//		spawnPoint = Vector2f(0, rngHeight);
//	}
//
//	return spawnPoint;
//}
//
//Color EnemySetColor(bool canDivide, int life, EnemyType type) {
//
//	Color color(rand() % 155 + 100,
//				rand() % 75,
//				rand() % 75);
//
//	//can divide and has multiple life
//	if (canDivide && life > 1) {	
//		//Yellow & Green
//		color = Color(150, 255, 0);
//	}
//	//can only divide
//	else if(canDivide) {
//		//yellow honey
//		color = Color(255, 195, 11);
//
//	}
//	//has multiple life only
//	else if (life > 1) {
//		//green forest
//		color = Color(11, 102, 35);
//	}
//
//	if (type == EnemyType::MINI) {
//		return Color::Magenta;
//	}
//
//	if (type == EnemyType::TELEPORTER) {
//		return Color::Blue;
//	}
//
//	return color;
//}
//
//
//void EnemySetShape(Enemy* pEnemy, CircleShape* pShape) {
//
//	int rngPointCount = rand() % 10 + 10;
//
//	if (pEnemy->shapeType == "Square") {
//		pShape->setPointCount(4);
//	}
//	else if (pEnemy->shapeType == "Pentagon") {
//		pShape->setPointCount(5);
//	}
//	else if (pEnemy->shapeType == "Hexagon") {
//		pShape->setPointCount(6);
//	}
//	else if (pEnemy->shapeType == "Heptagon") {
//		pShape->setPointCount(7);
//	}
//	else if (pEnemy->shapeType == "Octagon") {
//		pShape->setPointCount(8);
//	}
//	else if (pEnemy->shapeType == "Enneagone") {
//		pShape->setPointCount(9);
//	}
//	else if (pEnemy->shapeType == "Decagone") {
//		pShape->setPointCount(10);
//	}
//	else if (pEnemy->shapeType == "Polygon") {
//		pShape->setPointCount(rngPointCount);
//	}
//
//	if (pEnemy->hasOutline) {
//		pShape->setOutlineThickness(10);
//		pShape->setOutlineColor(Color(0, 126, 178));
//	}
//
//	pShape->setRadius(pEnemy->radius);
//	pShape->setOrigin(pEnemy->radius, pEnemy->radius);
//	pShape->setPosition(pEnemy->spawnPoint);
//	pShape->setFillColor(pEnemy->color);
//}
//
//float EnemySetRadius(EnemyType type, int life) {
//	float rngRadius = static_cast<float>(rand() % 60 + 20);
//	
//	if (type == EnemyType::MINI) {
//		return 10.0f;
//	}
//	else if (type == EnemyType::SNAKE) {
//		return 30.0f;
//	}
//	else if (life > 1) {
//		return rand() % 50 + 50;
//	}
//	return rngRadius;
//}
//int EnemySetSpeed(EnemyType type) {
//	int rngSpeed = rand() % 100 + 100;
//
//	if (type == EnemyType::MINI) {
//		return 1000;
//	}
//	return rngSpeed;
//}
//
//int EnemySetRotation() {
//	int rngRotation = rand() % 45 + 10;
//	return rngRotation;
//}
//
////SPAWN UP LEFT -> GO DOWN (RIGHT)
////SPAWN UP MIDDLE -> GO DOWN (RIGHT OR LEFT)
////SPAWN UP RIGHT -> GO DOWN (LEFT)
////SPAWN DONW LEFT -> GO UP (RIGHT)
////SPAWN DOWN MIDDLE -> GO UP (RIGHT OR LEFT)
////SPAWN DDOWN RIGHT -> GO UP (LEFT)
//Vector2f EnemySetDirectionX(float x, int width, int height, float speed, EnemyType type) {
//	Vector2f velocity = Vector2f (100.0f, 100.0f);
//	int rngSpeed = rand() % 100 + 100;
//	int rngDirection = rand() % 2; // 0 = gp straight| 1 = go right |2 = go left
//
//	if (type == EnemyType::MINI) {
//		rngSpeed = rand() % 500 + 500;
//	}
//	//spawn left or middle -> go right
//	if (rngDirection != 0) {
//		if (x <= width / 2 && rngDirection == 1) {
//			velocity = Vector2f(rngSpeed, speed);
//		}
//		//spawn right or middle -> go left
//		else if (x >= width / 2 && rngDirection == 2) {
//			velocity = Vector2f(-rngSpeed, speed);
//		}
//	}
//	//go straight 
//	else {
//		if (width != 0 && width != width) {
//			velocity = Vector2f(0.0f, speed);
//		}
//		//CORNER
//		else if(width == 0){
//			velocity = Vector2f(rngSpeed, speed);
//		}
//		else {
//			velocity = Vector2f(-rngSpeed, speed);
//		}
//	}
//	return velocity;
//}
//
////SPAWN LEFT DOWN -> GO RIGHT (UP)
////SPAWN LEFT MIDDLE -> GO RIGHT (UP OR DOWN)
////SPAWN LEFT UP	 -> GO RIGHT (DOWN)
////SPAWN RIGHT DONW -> GO LEFT (UP)
////SPAWN RIGTH MIDDLE -> GO LEFT (UP OR DOWN)
////SPAWN RIGHT UP -> GO LEFT (DOWN)
//Vector2f EnemySetDirectionY(float y, int width, int height, float speed, EnemyType type) {
//	Vector2f velocity = Vector2f (100.0f, 100.0f);
//	int rngSpeed = rand() % 100 + 100; 
//	int rngDirection = rand() % 2; // 0 = gp straight | 1 = go up | 2 = go down
//
//	if (type == EnemyType::MINI) {
//		rngSpeed = rand() % 500 + 500;
//	}
//	//spawn up or middle -> go right 
//	if (rngDirection != 0) {
//		if (y <= height / 2 && rngDirection == 1) {
//			velocity = Vector2f(speed, rngSpeed);
//		}
//		//spawn down or middle -> go left
//		else if (y >= height / 2 && rngDirection == 2) {
//			velocity = Vector2f(speed, -rngSpeed);
//		}
//	}
//	else {
//		if (height != 0 && height != height) {
//			velocity = Vector2f(speed, 0.0f);
//		}
//		//CORNER
//		else if (width == 0) {
//			velocity = Vector2f(speed, rngSpeed);
//		}
//		else {
//			velocity = Vector2f(speed, -rngSpeed);
//		}
//	}
//	return velocity;
//}
//
//Vector2f EnemySetVelocity(float x, float y, int width, int height, float speed, EnemyType type) {
//	Vector2f velocity;
//
//	//SPAWN UP
//	if (y == 0.0f) {
//		//Go down (right or left)
//		velocity = EnemySetDirectionX(x, width, height, speed, type);
//	}
//	//SPAWN DOWN
//	else if (y == height) {
//		//Go up (right or left)
//		velocity = EnemySetDirectionX(x, width, height, -speed, type);
//	}
//	//SPAWN LEFT
//	else if (x == 0.0f) {
//		//Go right (up or down)
//		velocity = EnemySetDirectionY(y, width, height, speed, type);
//	}
//	//SPAWN RIGHT
//	else if (x == width) {
//		//Go left (up or down)
//		velocity = EnemySetDirectionY(y, width, height, -speed, type);
//	}
//
//	return velocity;
//}
//
//int EnemySetLife(EnemyType type) {
//	int rngLife = rand() % 3 + 1;
//
//	if (type != EnemyType::BASIC) {
//		return 1;
//	}
//
//	return rngLife;
//}
//
//int EnemySetSize(float radius) {
//	int size = 1;
//
//	if (radius > 100) {
//		size = 3;
//	}
//	else if (radius > 50) {
//		size = 2;
//	}
//	return size;
//}
//
//int EnemySetScoreValue(float radius, EnemyType type) {
//	int scoreVal = (int)radius * 10;
//
//	if (type != EnemyType::BASIC) {
//		scoreVal *= 2;
//	}
//	return scoreVal;
//}
//
//bool EnemySetCanDivide(EnemyType type) {
//	int rngDivide = rand() % 101;
//	if (type == EnemyType::MINI || type == EnemyType::KAMIKAZE) {
//		return false;
//	}
//	return !(rngDivide % 5);
//}
//
//bool EnemySetFollowPlayer(EnemyType type) {
//	int rngFollow = rand() % 101 % 50;
//	if (type == EnemyType::MINI || type == EnemyType::SNAKE) {
//		return false;
//	}
//	else if (type == EnemyType::KAMIKAZE || type == EnemyType::TELEPORTER) {
//		return true;
//	}
//	return !(rngFollow % 3);
//}
//
//bool EnemySetHasOutline(EnemyType type) {
//	int rngOutline = rand() % 101;
//
//	if (type == EnemyType::MINI) {
//		return false;
//	}
//	return !(rngOutline % 4);
//}
//
////EnemyType EnemySetType() {
//
////}
//
//Enemy* EnemySnakeTail(Enemy* snakeHead) {
//	Enemy* snakeTail = new Enemy;
//
//	snakeTail->type = EnemyType::TAIL;
//	snakeTail->canDivide = false;
//	snakeTail->hasOutline = false;
//	snakeTail->followPlayer = false;
//	snakeTail->life = 0;
//	snakeTail->radius = snakeHead->radius/1.5f;
//	snakeTail->shape = snakeHead->shape;
//	snakeTail->shape.setOutlineThickness(0);
//	snakeTail->shape.setRadius(snakeTail->radius);
//	snakeTail->spawnPoint = Vector2f(snakeHead->shape.getPosition().x - snakeHead->radius * 2, snakeHead->shape.getPosition().y);
//	snakeTail->shape.setPosition(snakeTail->spawnPoint);
//	snakeTail->shape.setOrigin(snakeTail->radius, snakeTail->radius);
//	snakeTail->color = Color::Black;
//	snakeTail->shape.setFillColor(Color::Black);
//	snakeTail->speed = snakeHead->speed;
//	snakeTail->rotation = snakeHead->rotation;
//
//	return snakeTail;
//}
//
//Enemy* EnemyCreate(int width, int height) {
//	Enemy* enemy = new Enemy;
//	CircleShape shape;
//
//	//Type 
//	enemy->type = EnemySetType();
//	//special feature
//	enemy->canDivide = EnemySetCanDivide(enemy->type);
//	enemy->followPlayer = false; //EnemySetFollowPlayer(enemy->type);
//	enemy->hasOutline = EnemySetHasOutline(enemy->type);
//
//	//need
//	enemy->life = EnemySetLife(enemy->type);
//	enemy->radius = EnemySetRadius(enemy->type, enemy->life);	
//	enemy->size = EnemySetSize(enemy->radius);
//	enemy->scoreValue = EnemySetScoreValue(enemy->radius, enemy->type);
//
//	//Shape
//	enemy->shapeType = EnemySetShapeType();
//	enemy->spawnPoint = EnemySetSpawnPoint(width, height, enemy->type);
//	enemy->color = EnemySetColor(enemy->canDivide, enemy->life, enemy->type);
//	EnemySetShape(enemy, &shape);
//	enemy->shape = shape;
//
//	//Speed
//	enemy->speed = EnemySetSpeed(enemy->type);
//	enemy->rotation = EnemySetRotation();
//	enemy->velocity = EnemySetVelocity(enemy->spawnPoint.x, enemy->spawnPoint.y, width, height, enemy->speed, enemy->type);
//
//	//bool
//	enemy->isAlive = true;
//	enemy->hasSpawn = false;
//
//	return enemy;
//}
//
//
//void EnemyUpdate(Enemy* pEnemy, int width, int height, float deltaTime, float deltaAngle, Player* pPlayer, list<Enemy*>& enemyList) {
//	Vector2f velocity = pEnemy->velocity;
//	
//	deltaAngle = deltaTime * IIM_PI * 2.0f * pEnemy->rotation;
//	//TELEPORTER
//	if (pEnemy->type == EnemyType::TELEPORTER) {
//		pEnemy->timeBeforeTeleport -= deltaTime;
//		if (pEnemy->timeBeforeTeleport <= 0) {
//			//get player position
//			if (pEnemy->teleportPosition == Vector2f(-1.0f, -1.0f)) {
//				pEnemy->teleportPosition = Vector2f(pPlayer->triangle.getPosition().x, pPlayer->triangle.getPosition().y);
//			}
//			//stop move
//			velocity = Vector2f(0, 0);
//			//wait
//			if (pEnemy->stopMoveTime <= 0) {
//				//teleport
//				pEnemy->shape.setPosition(pEnemy->teleportPosition);
//				pEnemy->timeBeforeTeleport = 5.0f;
//				pEnemy->stopMoveTime = 2.0f;
//				//retreive velocity
//				velocity = pEnemy->velocity;
//			}
//			
//			//stop movement time reduce
//			pEnemy->stopMoveTime -= deltaTime;
//		}
//	}
//
//	//draw circle of teleportation
//	if	(pEnemy->type == EnemyType::TELEPORTER && pEnemy->teleportPosition != Vector2f(-1.0f, -1.0f)) {
//		pEnemy->teleportCircle.setRadius(pEnemy->radius);
//		pEnemy->teleportCircle.setFillColor(Color(0, 0, 150, 150));
//		pEnemy->teleportCircle.setOrigin(pEnemy->teleportCircle.getRadius(), pEnemy->teleportCircle.getRadius());
//		pEnemy->teleportCircle.setPosition(pEnemy->teleportPosition);
//	}
//
//	if (pEnemy->type == EnemyType::KAMIKAZE) {
//		EnemyFollowPlayer(pEnemy, pPlayer, deltaTime);
//		pEnemy->timerBeforeExplode -= deltaTime;
//		if (pEnemy->timerBeforeExplode <= 0) {
//			//stop mvt
//			velocity = Vector2f(0, 0);
//			//rotate a lot
//			pEnemy->rotation = 180;
//			//wait
//			if (pEnemy->stopMoveTime <= 0) {
//				//explode
//				EnemyDivide(pEnemy, enemyList, width, height);
//				pEnemy->isAlive = false;
//			}
//
//			pEnemy->stopMoveTime -= deltaTime;
//		}
//	}
//
//	//Move Enemy
//	if (pEnemy->type != EnemyType::SNAKE) {
//		pEnemy->shape.move(velocity * deltaTime);
//		//pEnemy->shape.setPosition(pEnemy->shape.getPosition() + pEnemy->velocity * deltaTime);
//		pEnemy->shape.rotate(deltaAngle);
//	}
//
//	//SNake type move pattern
//	if (pEnemy->type == EnemyType::SNAKE || pEnemy->type == EnemyType::TAIL) {
//		int speedX = 20;
//		int speedY = 400;
//		int phi = 5;
//		pEnemy->snakeX--;
//		pEnemy->snakeY = sin(ConvertDegToRad(pEnemy->snakeX * phi));
//		pEnemy->shape.move(ConvertDegToRad(pEnemy->snakeX) * deltaTime * speedX, pEnemy->snakeY * speedY * deltaTime);
//
//	}
//	//Follow player
//	if (pEnemy->followPlayer) {
//		EnemyFollowPlayer(pEnemy, pPlayer, deltaTime);
//	}
//
//	//loop map
//	//down
//	if (pEnemy->shape.getPosition().x > width) pEnemy->shape.setPosition(0.0f, pEnemy->shape.getPosition().y);
//	//up
//	if (pEnemy->shape.getPosition().x < 0) pEnemy->shape.setPosition((float)width, pEnemy->shape.getPosition().y);
//	//right
//	if (pEnemy->shape.getPosition().y > height) pEnemy->shape.setPosition(pEnemy->shape.getPosition().x, 0.0f);
//	//left
//	if (pEnemy->shape.getPosition().y < 0) pEnemy->shape.setPosition(pEnemy->shape.getPosition().x, (float)height);
//}
//
//void EnemyDivide(Enemy* enemy, list<Enemy*>& pEnemyList, int width, int height) {
//
//	for (int count = 0; count < enemy->size * 3; count++) {
//		Enemy* divide = new Enemy;
//		divide = EnemyCreate(width, height);
//		EnemyDivideSetParameters(divide, enemy, count);
//		pEnemyList.push_back(divide);
//	}
//}
//
//void EnemyDivideSetParameters(Enemy* divide, Enemy* enemy, int index) {
//	//Spawn point X = radius * cos(alpha)
//	//Spawn point y = radius * sin(alpha)
//	//Alpha = 360 degree / (number of enemy to spawn) * current index of enemy to spawn
//	float alpha = 360.0f / (enemy->size * 3.0f) * index;
//	float posX = enemy->radius * cos(ConvertDegToRad(alpha));
//	float posY = enemy->radius * sin(ConvertDegToRad(alpha));
//
//	divide->type = EnemyType::DIVIDE;
//	divide->life = 1;
//	divide->hasOutline = false;
//	divide->canDivide = false;
//	divide->radius = enemy->radius / 2;
//	divide->shape.setRadius(divide->radius);
//	divide->spawnPoint = Vector2f(enemy->shape.getPosition().x + posX, enemy->shape.getPosition().y + posY);
//	divide->shape.setPosition(divide->spawnPoint);
//	divide->velocity = Vector2f(posX, posY);
//	divide->shape.setOutlineThickness(0);
//	divide->shape.setOrigin(divide->radius, divide->radius);
//	divide->shape.setFillColor(Color(255, 0, 0));
//	
//	if (enemy->type == EnemyType::KAMIKAZE) {
//		divide->velocity *= 30.0f;
//	}
//	//not destroying immediatly (and not having super vfx effect)
//	divide->invicibleTime = 0.2f;
//}
//
//void EnemyFollowPlayer(Enemy* pEnemy, Player* pPlayer, float deltaTime) {
//	
//	//pythagore & vector normalization
//	float xEnemy = pEnemy->shape.getPosition().x;
//	float yEnemy = pEnemy->shape.getPosition().y;
//	float xPlayer = pPlayer->triangle.getPosition().x;
//	float yPlayer = pPlayer->triangle.getPosition().y;
//
//	float dx = xPlayer - xEnemy; //difference of x position 
//	float dy = yPlayer - yEnemy; // difference of y position 
//	float lenght = sqrt(pow(dx, 2) + pow(dy, 2)); //distance between enemy and player
//	Vector2f direction = (pPlayer->triangle.getPosition() - pEnemy->shape.getPosition()) / lenght; //normalize vector
//
//	float speed = 500.0f;
//	pEnemy->shape.move(direction * speed * deltaTime);
//}
//
//void EnemyTeleport() {
//
//}