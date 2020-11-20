#include "Score.h"

void ScoreUpdate(EnemyType type, int& score, int comboCount, Text &scoreText) {
	switch (type)
	{
	case EnemyType::BASIC:
		score += 10 * comboCount;
		break;
	case EnemyType::MINI:
		score += 100 * comboCount;
		break;
	case EnemyType::TELEPORTER:
		score += 20 * comboCount;
		break;
	case EnemyType::SNAKE:
		score += 30 * comboCount;
		break;
	case EnemyType::KAMIKAZE:
		score += 30 * comboCount;
		break;
	case EnemyType::FOLLOWER:
		score += 20 * comboCount;
		break;
	case EnemyType::DIVIDER:
		score += 30 * comboCount;
		break;
	case EnemyType::SUB:
		score += 10 * comboCount;
		break;
	case EnemyType::LIFER:
		score += 30 * comboCount;
		break;
	case EnemyType::LIFEDIVIDER:
		score += 40 * comboCount;
		break;
	default:
		score += 10 * comboCount;
		break;
	}
	scoreText.setString(to_string(score));
}