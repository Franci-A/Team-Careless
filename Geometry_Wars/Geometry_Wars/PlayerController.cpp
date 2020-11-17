#include "PlayerController.h"

sf::Vector2f PlayerMove(Player& player, sf::Vector2f localPosition, float deltaTime, int screenWidth, int screenHeight) {

	// limit screen
	float x = localPosition.x - player.triangle.getPosition().x; //difference of x position 
	float y = localPosition.y - player.triangle.getPosition().y; // difference of y position 
	float lenght = sqrt(pow(x, 2) + pow(y, 2)); //distance between enemy and player
	sf::Vector2f direction = (localPosition - player.triangle.getPosition()) / lenght; //normalize vector*

	bool outOfScreenX = player.triangle.getPosition().x <= player.triangle.getRadius() * 2 || player.triangle.getPosition().x >= screenWidth - player.triangle.getRadius() * 2;
	bool outOfScreenY = player.triangle.getPosition().y <= player.triangle.getRadius() * 2 || player.triangle.getPosition().y >= screenHeight - player.triangle.getRadius() * 2;
	bool cursorInScreenX = localPosition.x > player.triangle.getRadius() * 2 && localPosition.x < screenWidth - player.triangle.getRadius() * 2;
	bool cursorInScreenY = localPosition.y > player.triangle.getRadius() * 2 && localPosition.y < screenHeight - player.triangle.getRadius() * 2;

	if (outOfScreenX && outOfScreenY && (localPosition.x > player.triangle.getRadius() * 2 && localPosition.x < screenWidth - player.triangle.getRadius() * 2) && (localPosition.y > player.triangle.getRadius() * 2 && localPosition.y < screenHeight - player.triangle.getRadius() * 2) ){
	}
	else if (outOfScreenX && outOfScreenY) {
		direction = sf::Vector2f(0, 0);
	}
	else if (outOfScreenX && !cursorInScreenX) {
		direction.x = 0;
	}
	else if (outOfScreenX && cursorInScreenX) {
	}
	else if (outOfScreenY && !cursorInScreenY) {
		direction.y = 0;
	}
	else if (outOfScreenY && cursorInScreenY){

	}
	else if(!outOfScreenX && !outOfScreenY) {
	}
	else {
		return sf::Vector2f(0, 0);
	}
	player.triangle.move(direction * player.speed * deltaTime);
	return sf::Vector2f(direction * player.speed * deltaTime);
}

void PlayerRotation(Player& player, sf::Vector2f localPosition) {

	const float PI = 3.14159265;

	float dx = player.triangle.getPosition().x - localPosition.x;
	float dy = player.triangle.getPosition().y - localPosition.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	player.triangle.setRotation(rotation- 90);
}

//Bullet* PlayerShot(bool& drawBullet, sf::Vector2f localPosition, Player player, Bullet* bullet) {
//	bullet = SpawnBall(player.triangle.getPosition().x, player.triangle.getPosition().y, localPosition.x, localPosition.y, BALL_TYPE::DEFAULT, bullet);
//	bullet->visual.setPosition(player.triangle.getPosition().x + bullet->X_offset * 5, player.triangle.getPosition().y + bullet->Y_offset*5 );
//	bullet->visual.setRadius(10);
//	bullet->visual.setOrigin(10, 10);
//	drawBullet = true;
//	return bullet;
//}

void PlayerShot(bool& drawBullet, sf::Vector2f localPosition, Player player) {
	std::list<Bullet*>::iterator it = player.bulletList.begin();
	while (it != player.bulletList.end())
	{
		(*it) = SpawnBall(player.triangle.getPosition().x, player.triangle.getPosition().y, localPosition.x, localPosition.y, (*it));
		(*it)->visual.setPosition(player.triangle.getPosition().x + (*it)->X_offset * 5, player.triangle.getPosition().y + (*it)->Y_offset*5 );
		it++;
	}
	drawBullet = true;
}

//
Bullet* AddNewBullet(Bullet_Powerup powerup)
{
	Bullet* bullet = new Bullet;

	bullet->type = powerup.type;
	bullet->visual = powerup.visual;
	bullet->speed = powerup.speed;

	if (bullet->type == BALL_TYPE::DEFAULT) {
		bullet->visual.setFillColor(sf::Color(255, 255, 255, 255));
		bullet->visual.setOutlineThickness(0);
	}
	else if (bullet->type == BALL_TYPE::TRIPLE) {
		bullet->visual.setFillColor(sf::Color(148, 214, 208, 255));
		bullet->visual.setOutlineThickness(1.5f);
		bullet->visual.setOutlineColor(sf::Color(255, 255, 255, 255));
	}

	bullet->visual.setOrigin(bullet->visual.getRadius(), bullet->visual.getRadius());
	
	return bullet;
}

void PowerupSwap(Player* player, BALL_TYPE type, std::map<BALL_TYPE, Bullet_Powerup> bulletpedia)
{
	player->bulletList.clear();
	for (int i = 0; i < bulletpedia[type].ammo; i++) {
		player->bulletList.push_back(AddNewBullet(bulletpedia[type]));
	}
	player->bulletType = type;
}