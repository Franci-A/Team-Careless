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

	this->direction = Vector2f(posX, posY);

	this->radiusReduc = 0.93f;
}

VFX::VFX(Player* pPlayer, bool invicibleBonus) {
	this->shape.setPointCount(4);
	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setPosition(pPlayer->triangle.getPosition());
	this->shape.setRotation(pPlayer->triangle.getRotation() + 45);

	this->speed = 0.f;
	this->time = 0.7f;

	if (invicibleBonus) {
		this->shape.setFillColor(Color::Color(
			pPlayer->triangle.getFillColor().r,
			pPlayer->triangle.getFillColor().g,
			pPlayer->triangle.getFillColor().b,
			185
		));
		this->radiusReduc = 0.97f;
	}
	else if (pPlayer->triangle.getOutlineThickness() > 0) {
		this->shape.setFillColor(Color::Color(
			pPlayer->triangle.getOutlineColor().r,
			pPlayer->triangle.getOutlineColor().g,
			pPlayer->triangle.getOutlineColor().b,
			130
		));
		this->radiusReduc = 0.9f;
	}
	else {
		this->shape.setFillColor(Color::Color(255, 255, 255, 150));
		this->radiusReduc = 0.83f;
	}
}

VFX::~VFX() {}

void VFX::move(float deltaTime) {
	this->shape.move(this->direction * this->speed * deltaTime);
	this->shape.setRadius(this->shape.getRadius() * this->radiusReduc);
	this->shape.setOrigin(this->shape.getRadius(), this->shape.getRadius());
}
