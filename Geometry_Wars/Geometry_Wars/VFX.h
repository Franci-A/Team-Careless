#pragma once
#include"EnemyClass.h"
#include"VFXClass.h"

void InstantiateVFX(Enemy* pEnemy, list<VFX*> &vfxList);
void DestroyVFX(list<VFX*>& listVFX, float deltaTime);