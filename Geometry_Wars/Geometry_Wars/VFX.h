#pragma once
#include"EnemyClass.h"
#include"VFXClass.h"

void InstantiateVFX(Enemy* pEnemy, list<VFX*> &vfxList);
void InstantiatePlayerVFX(Player* pPlayer, list<VFX*>& vfxList, bool invicibleBonus);
void DestroyVFX(list<VFX*>& listVFX, float deltaTime);