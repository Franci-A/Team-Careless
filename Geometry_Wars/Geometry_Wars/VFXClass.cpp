#include "VFXClass.h"

VFX::VFX(int divideNumber, Enemy* pEnemy, int i) {
	float alpha = 360.0f / divideNumber * i;			//Alpha = 360 degree / (number of enemy to spawn) * index of enemy
	if (pEnemy->type == EnemyType::MINI) {				// radius
		radius = pEnemy->GetShape().getRadius() * ((rand() % (8 - 5) + 5) * 0.1f);
	}
	else {
		radius = (pEnemy->GetShape().getRadius() * (rand() % (4 - 2) + 2) * 0.1f + (rand() % 7) - 3);
	}
	float posX = radius * cos(ConvertDegToRad(alpha));		//Spawn point X = radius * cos(alpha)
	float posY = radius * sin(ConvertDegToRad(alpha));		//Spawn point y = radius * sin(alpha)
	//int rngColor = rand() % 6;
	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setPosition(Vector2f(pEnemy->GetPosition().x + posX, pEnemy->GetPosition().y + posY));
	
	this->shape.setRotation(rand() % 180);
	this->shape.setPointCount(/*pEnemy->GetShape().getPointCount()*/3);

	this->shape.setFillColor(Color::Color(
		pEnemy->GetShape().getFillColor().r,
		pEnemy->GetShape().getFillColor().g,
		pEnemy->GetShape().getFillColor().b,
		150
	));
	/*if (rngColor == 0) {
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
	}*/

	this->direction = Vector2f(posX, posY);
}

VFX::~VFX() {}

void VFX::move(float deltaTime) {
	this->shape.move(this->direction * this->speed * deltaTime);
	this->shape.setRadius(this->shape.getRadius() * 0.93f);
}
