#include "Enemy.h"

//FUNCTION
void EnemyDivide(Enemy* pEnemy, list<Enemy*>& pEnemyList) {

	for (int count = 0; count < pEnemy->GetDivideNumber(); count++) {
		Enemy* divide = new Enemy(pEnemy->GetRadius(), pEnemy->GetPointCount(), pEnemy->GetDivideNumber(), pEnemy->GetPosition(), count, EnemyType::SUB, pEnemy->type);
		pEnemyList.push_back(divide);
	}
}