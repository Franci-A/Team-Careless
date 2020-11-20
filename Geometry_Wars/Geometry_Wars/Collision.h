#pragma once
#include "PlayerController.h"
#include "Bullet.h"
#include "Bonus.h"

bool HasCollided(Player player, float x, float y, float rayon);
bool HasCollidedBullet(Bullet bullet, float x, float y, float rayon);
bool HasCollidedBonus(Bonus bonus, float x, float y, float rayon, bool bombIsExploding);