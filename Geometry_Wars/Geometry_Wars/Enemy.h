#pragma once
#include "EnemyClass.h"

#include <SFML/Audio/Sound.hpp>
using namespace sf;

void EnemyCreate(list<Enemy*>& enemyList, int& countEnemy, int maxEnemy, bool pause, Time& elapsedTimeSpawn, Clock& clockSpawn, float spawnTime, int width, int height);
void EnemyDivide(Enemy* enemy, list<Enemy*>& pEnemyList);
void EnemyDestroy(list<Enemy*> &enemyList, int &countEnemy, Sound sound);