#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>;
#include <math.h>

using namespace std;
using namespace sf;

//class Enemy : public Transformable {
//
//public :
//
//	CircleShape GetShape() {
//		return shape;
//	}
//
//	Color GetColor() {
//		return shape.getFillColor();
//	}
//
//	Vector2f GetSpawnPoint() {
//		return spawnPoint;
//	}
//
//	Vector2f GetPosition() {
//		return position;
//	}
//
//	Vector2f GetVelocity() {
//		return velocity;
//	}
//
//	FloatRect GetHitBox() {
//		return hitBox;
//	}
//	float GetSpeed() {
//		return speed;
//	}
//
//	float GetRotationSpeed() {
//		return rotationSpeed;
//	}
//
//	float GetAngle() {
//		return angle;
//	}
//
//	//float GetRadius() {
//	//	return radius;
//	//}
//
//	float GetSize() {
//		return size;
//	}
//
//	int GetLife() {
//		return life;
//	}
//
//	bool GetBool() {
//		return isAlive;
//	}
//
//	
//	void SetShape(CircleShape s) {
//		shape = s;
//	};
//
//	void SetColor(Color c) {
//		color = c;
//	}
//
//	void SetPosition(Vector2f p) {
//		position = p;
//	}
//
//	void SetVelocity(Vector2f v) {
//		velocity = v;
//	}
//
//	void SetSpeed(float s) {
//		speed = s;
//	}
//
//	void SetRotationSpeed(float s) {
//		rotationSpeed = s;
//	}
//
//	void SetAngle(float a) {
//		angle = a;
//	}
//
//	//void SetRadius() {
//	//	radius = shape.getRadius();
//	//}
//
//	void SetLife(int l) {
//		life = l;
//	}
//
//	void SetisAlive(bool b) {
//		isAlive = b;
//	}
//
//private :
//	CircleShape shape;
//	Color color;
//	Vector2f spawnPoint;
//	Vector2f position;
//	Vector2f velocity;
//	FloatRect hitBox;
//	float speed;
//	float rotationSpeed;
//	float angle;	
//	float radius = 10.0f; // radius of circle shape
//	float size;
//	int life = 1;
//	bool isAlive;
//
//};

struct Enemy {
	CircleShape shape;
	Color color;
	Vector2f spawnPoint;
	Vector2f position;
	Vector2f velocity;
	FloatRect hitBox;
	float speed;
	float rotationSpeed;
	float angle;	
	float radius = 10.0f; // radius of circle shape
	float size;
	int life = 1;
	bool isAlive;
};

void ShapeDraw(CircleShape &shape);
Vector2f ShapeSetSpawnPoint(int width, int height);
Color ShapeSetColor();
void EnemySetSpeed();
void EnemySetRotationSpeed();
void EnemySetAngle();
Enemy EnemyCreate(int width, int height);
void EnemyUpdatePosition();