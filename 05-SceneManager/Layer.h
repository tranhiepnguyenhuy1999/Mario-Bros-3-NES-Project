#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CLayer : public CGameObject {
	static CLayer* __instance;

public:
	CLayer(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	
	int IsBlocking() { return 0; }

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	static CLayer* GetInstance();

};