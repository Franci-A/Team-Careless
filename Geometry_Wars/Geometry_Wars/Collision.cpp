#include "Collision.h"

bool HasCollided(Player player, float x, float y, float rayon) {
	float distanceAB = sqrt(powf(x - player.triangle.getPosition().x, 2) + powf(y - player.triangle.getPosition().y, 2));
	
	if( distanceAB <= rayon + player.triangle.getRadius()){
		return true;
	}

	return false;
}


bool HasCollidedBullet(Bullet bullet, float x, float y, float rayon) {
	float distanceAB = sqrt(powf(x - bullet.visual.getPosition().x, 2) + powf(y - bullet.visual.getPosition().y, 2));

	if( distanceAB <= rayon + bullet.visual.getRadius()){
		return true;
	}

	return false;
}

bool HasCollidedBonus(Bonus bonus, float x, float y, float rayon, bool bombIsExploding) {
	if (bombIsExploding) {
		float distanceAB = sqrt(powf(x - bonus.bombShape.getPosition().x, 2) + powf(y - bonus.bombShape.getPosition().y, 2));

		if (distanceAB <= rayon + (bonus.bombShape.getRadius())) {
			return true;
		}
	}

	return false;
}