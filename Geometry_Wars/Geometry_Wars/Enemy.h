#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>;
#include <math.h>

using namespace std;
using namespace sf;

class Enemy : public Transformable {

public :
	bool GetBool() {
		return is_alive;
	}

	Vector2f GetDirection() {
		return direction;
	}

	Vector2f GetPosition() {
		return position;
	}

	CircleShape GetShape() {
		return shape;
	}

	float GetSpeed() {
		return speed;
	}

	float GetRotationSpeed() {
		return rotationSpeed;
	}

	float GetAngle() {
		return angle;
	}

	float GetRadius() {
		return radius;
	}

	float GetSize() {
		return size;
	}

	int GetLife() {
		return life;
	}
private :

	bool is_alive;
	Vector2f direction;
	Vector2f position;
	Vector2f spawnPoint;
	CircleShape shape;
	float speed;
	float rotationSpeed;
	float angle;	
	float radius; //for circle shape
	float size;
	int life = 1;

	
};

//CircleShape DrawShape(Enemy enemy);
CircleShape DrawShape(string enemy, int rng);
void EnemySetPosition(CircleShape &shape, int width, int height);
void EnemySetColor(CircleShape &shape);
CircleShape EnemyCreate(int width, int height);