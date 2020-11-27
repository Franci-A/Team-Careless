#pragma once
#include "EnemyClass.h"
#include "VFXClass.h"

#include <SFML/Audio/Sound.hpp>
using namespace sf;

void EnemyCreate(list<Enemy*>& enemyList, int& countEnemy, int maxEnemy, bool pause, Time& elapsedTimeSpawn, Clock& clockSpawn, float& spawnTime, int width, int height, Clock clockWave);
void EnemyDivide(Enemy* enemy, list<Enemy*>& pEnemyList);
void EnemyDestroy(list<Enemy*> &enemyList, int &countEnemy, Sound sound, list<VFX*>& vfxList);