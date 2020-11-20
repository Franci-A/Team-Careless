#include "VFX.h"

void InstantiateVFX(Enemy* pEnemy, list<VFX*> &vfxList) {
	int divideNumber = 60;

	for (int i = 0; i < divideNumber; i++) {
		VFX* vfx = new VFX(divideNumber, pEnemy, i);
		//debug
		cout << vfx->circle.getPosition().x << endl;
		vfxList.push_back(vfx);
	}
}

void DestroyVFX(list<VFX*>& vfxList, float deltaTime) {
	if (!vfxList.empty()) {
		auto it = vfxList.begin();

		while (it != vfxList.end()) {
			if (!(*it)->isAlive) {
				delete (*it);
				it = vfxList.erase(it);
			}
			else {
				it++;
			}
		}
	}
}