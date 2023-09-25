#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_STATIC	11002

#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_TYPE_STATIC 1

class CCoin : public CGameObject {
	int type;

public:
	CCoin(float x, float y, int type=0) : CGameObject(x, y) {
		this->type = type;
	}
	
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	int IsBlocking() { return 0; }
};