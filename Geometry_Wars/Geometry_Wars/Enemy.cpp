#include "Enemy.h"

void EnemyCreate(list<Enemy*> &enemyList,int &countEnemy,int maxEnemy,bool pause,Time &elapsedTimeSpawn,Clock &clockSpawn, float spawnTime, int width, int height, Clock clockWave) {
	elapsedTimeSpawn = clockSpawn.getElapsedTime();
	Time elapsedTimeWave = clockWave.getElapsedTime();
	if (elapsedTimeSpawn.asSeconds() > spawnTime && countEnemy < maxEnemy && !pause)
	{
		if (elapsedTimeWave.asSeconds() > 90.0f) {
			Enemy* enemy = new Enemy(width, height);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 80.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::TELEPORTER);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 70.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::LIFEDIVIDER);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 60.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::KAMIKAZE);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 50.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::DIVIDER);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 40.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::LIFER);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 30.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::FOLLOWER);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 20.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::MINI);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 10.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::SNAKE);
			enemyList.push_back(enemy);
		}
		else if (elapsedTimeWave.asSeconds() > 0.0f) {
			Enemy* enemy = new Enemy(width, height, EnemyType::BASIC);
			enemyList.push_back(enemy);
		}
		clockSpawn.restart();
		countEnemy++;
	}
}

void EnemyDivide(Enemy* pEnemy, list<Enemy*>& pEnemyList) {
	if (pEnemy->type == EnemyType::LIFEDIVIDER && pEnemy->GetLife() == 3) {
		for (int count = 0; count < 2; count++) {
			Enemy* divide = new Enemy(pEnemy, count);
			pEnemyList.push_back(divide);
		}
	}
	else {
		for (int count = 0; count < pEnemy->GetDivideNumber(); count++) {
			Enemy* divide = new Enemy(pEnemy->GetRadius(), pEnemy->GetPointCount(), pEnemy->GetDivideNumber(), pEnemy->GetPosition(), count, EnemyType::SUB, pEnemy->type);
			pEnemyList.push_back(divide);
		}
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