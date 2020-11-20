#include "VFXClass.h"

VFX::VFX(int divideNumber, Enemy* pEnemy, int i) {
	float alpha = 360.0f / divideNumber * i;			//Alpha = 360 degree / (number of enemy to spawn) * index of enemy
	float posX = radius * cos(ConvertDegToRad(alpha));		//Spawn point X = radius * cos(alpha)
	float posY = radius * sin(ConvertDegToRad(alpha));		//Spawn point y = radius * sin(alpha)
	int rngColor = rand() % 6;
	this->circle.setRadius(10);
	this->circle.setOrigin(radius, radius);
	this->circle.setPosition(Vector2f(pEnemy->GetPosition().x + posX, pEnemy->GetPosition().y + posY));

	if (rngColor == 0) {
		this->circle.setFillColor(Color(255, 0, 0, 100));
	}
	else if (rngColor == 1) {
		this->circle.setFillColor(Color(0, 255, 0, 100));
	}
	else if (rngColor == 2) {
		this->circle.setFillColor(Color(0, 0, 255, 100));
	}
	else if (rngColor == 3) {
		this->circle.setFillColor(Color(255, 255, 0 , 100));
	}
	else if (rngColor == 4) {
		this->circle.setFillColor(Color(0, 255, 255, 100));
	}
	else if (rngColor == 5) {
		this->circle.setFillColor(Color(255, 0, 255, 100));
	}

	this->direction = Vector2f(posX, posY);
}

VFX::~VFX() {}

void VFX::move(float deltaTime) {
	this->circle.move(this->direction * this->speed * deltaTime);
}
