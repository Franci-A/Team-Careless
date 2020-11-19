#pragma once
#include "PlayerController.h"
#include "Bullet.h"

bool HasCollided(Player player, float x, float y, float rayon);
bool HasCollidedBullet(Bullet bullet, float x, float y, float rayon);