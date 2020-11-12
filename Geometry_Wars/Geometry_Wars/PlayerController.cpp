#include "PlayerController.h"



void PlayerMove(Player& player, sf::Vector2f localPosition, float deltaTime) {
	float x = 0;
	float y = 0;
	if (player.triangle.getPosition().x + 20 <= localPosition.x) {
		x = player.speed;
	}
	else if (player.triangle.getPosition().x + 20 > localPosition.x) {
		x = -player.speed;
	}
	else {
		x = 0;
	}


	if (player.triangle.getPosition().y + 20 <= localPosition.y) {
		y = player.speed;
	}
	else if (player.triangle.getPosition().y + 20 > localPosition.y) {
		y = -player.speed;
	}
	else {
		y = 0;
	}
	player.triangle.move(x, y);
}

void PlayerRotation(Player& player, sf::Vector2f localPosition) {

	const float PI = 3.14159265;

	float dx = player.triangle.getPosition().x - localPosition.x;
	float dy = player.triangle.getPosition().y - localPosition.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	player.triangle.setRotation(rotation- 90);
}

Bullet* PlayerShot(bool& drawBullet, sf::Vector2f localPosition, Player player, Bullet* bullet) {
	bullet = SpawnBall(player.triangle.getPosition().x, player.triangle.getPosition().y, localPosition.x, localPosition.y, BALL_TYPE::DEFAULT, bullet);
	bullet->visual.setPosition(player.triangle.getPosition().x + bullet->X_offset, player.triangle.getPosition().y + bullet->Y_offset );
	bullet->visual.setRadius(10);
	bullet->visual.setOrigin(10, 10);
	drawBullet = true;
	return bullet;
}