//#include "Enemy.h"

//void EnemyDivide(Enemy* pEnemy, list<Enemy*>& pEnemyList, int width, int height) {
//
//	for (int count = 0; count < pEnemy->GetDivideNumber(); count++) {
//		Enemy* divide = new Enemy(pEnemy->GetRadius(), pEnemy->GetPointCount(), pEnemy->GetDivideNumber(), pEnemy->GetPosition(), EnemyType::SUB);
//		pEnemyList.push_back(divide);
//	}
//}

//	
//	if (enemy->type == EnemyType::KAMIKAZE) {
//		divide->velocity *= 30.0f;
//	}
//	//not destroying immediatly (and not having super vfx effect)
//	divide->invicibleTime = 0.2f;
//}
//int EnemySetLife(EnemyType type) {
//	int rngLife = rand() % 3 + 1;
//
//	if (type != EnemyType::BASIC) {
//		return 1;
//	}
//
//	return rngLife;
//}
//int EnemySetScoreValue(float radius, EnemyType type) {
//	int scoreVal = (int)radius * 10;
//
//	if (type != EnemyType::BASIC) {
//		scoreVal *= 2;
//	}
//	return scoreVal;
//}