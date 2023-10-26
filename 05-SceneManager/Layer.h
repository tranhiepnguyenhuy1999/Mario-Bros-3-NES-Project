#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define LAYER_STATE_FADING_FROM_0_TO_1 100
#define LAYER_STATE_FADING_FROM_1_TO_0 200

#define LAYER_COUNT_TIMEOUT 50

class CLayer : public CGameObject {
	static CLayer* __instance;

	BOOLEAN isActive;

	float alpha;

	ULONGLONG count_start;

public:
	CLayer(float x, float y) : CGameObject(x, y) {
		count_start = -1;
		alpha = 0.0f;
		isActive = false;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	virtual int IsBlocking() { return 0;}

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	virtual void SetState(int state);
	
	void closeWindow() {
		isActive = true;
		SetState(LAYER_STATE_FADING_FROM_0_TO_1);
	};
	void OpenWindow() {
		isActive = true;
		SetState(LAYER_STATE_FADING_FROM_1_TO_0);
	};

	bool IsActive() {
		return isActive;
	}

	static CLayer* GetInstance();

};