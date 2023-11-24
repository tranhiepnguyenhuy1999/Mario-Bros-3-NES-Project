#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CNormalObjectWithAni : public CGameObject {
	int aniId;
public:
	CNormalObjectWithAni(float x, float y, int obj_aniId) : CGameObject(x, y) {
		aniId = obj_aniId;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};