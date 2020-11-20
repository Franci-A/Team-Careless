#include "Enemy.h"

void EnemyCreate(list<Enemy*> &enemyList,int &countEnemy,int maxEnemy,bool pause,Time &elapsedTimeSpawn,Clock &clockSpawn, float spawnTime, int width, int height) {
	elapsedTimeSpawn = clockSpawn.getElapsedTime();
	if (elapsedTimeSpawn.asSeconds() > spawnTime && countEnemy < maxEnemy && !pause)
	{
		Enemy* enemy = new Enemy(width, height, EnemyType::LIFER);
		enemyList.push_back(enemy);
		clockSpawn.restart();
		countEnemy++;
	}
}

void EnemyDivide(Enemy* pEnemy, list<Enemy*>& pEnemyList) {

	for (int count = 0; count < pEnemy->GetDivideNumber(); count++) {
		Enemy* divide = new Enemy(pEnemy->GetRadius(), pEnemy->GetPointCount(), pEnemy->GetDivideNumber(), pEnemy->GetPosition(), count, EnemyType::SUB, pEnemy->type);
		pEnemyList.push_back(divide);
	}
}

void EnemyDestroy(list<Enemy*> &enemyList, int &countEnemy, Sound sound) {
	if (!enemyList.empty()) {
		auto it = enemyList.begin();

		while (it != enemyList.end()) {

			if (!(*it)->isAlive) {

				sound.play();
				delete (*it);
				it = enemyList.erase(it);
				countEnemy--;
			}
			else {
				it++;
			}
		}
	}
}