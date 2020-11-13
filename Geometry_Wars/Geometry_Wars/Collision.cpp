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