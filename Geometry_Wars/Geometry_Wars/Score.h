#pragma once
#include <SFML/Graphics.hpp>
#include "EnemyClass.h"

using namespace sf;
using namespace std;

void ScoreUpdate(EnemyType type, int &score, int comboCount, Text &scoreText);