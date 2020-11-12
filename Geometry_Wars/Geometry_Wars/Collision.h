#pragma once
#include "Enemy.h"
#include "PlayerController.h"
#include "Bullet.h"

bool HasCollided(Player player, int x, int y, int rayon);
bool HasCollidedBullet(Bullet bullet, int x, int y, int rayon);