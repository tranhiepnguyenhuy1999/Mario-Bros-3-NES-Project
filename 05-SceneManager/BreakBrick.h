#pragma once
#include "debug.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BREAK_BRICK_MOVING_SPEED 0.05f

#define BREAK_BRICK_TRANSFORM_TO_COIN_TIMEOUT 10000

#define ID_ANI_BREAK_BRICK_NORMAL 10024
#define ID_ANI_BREAK_BRICK_TYPE2_TOUCHED 10003
#define ID_ANI_BREAK_BRICK_TRANSFORM_TO_COIN 11002

#define BREAK_BRICK_BBOX_WIDTH 16
#define BREAK_BRICK_BBOX_HEIGHT 16

#define BREAK_BRICK_TYPE_NORMAL 1
#define BREAK_BRICK_TYPE_SPECIAL 2

#define BREAK_BRICK_STATE_NORMAL 100
#define BREAK_BRICK_STATE_TOUCHED 200
#define BREAK_BRICK_STATE_TRANSFORM_TO_COIN 300


class CBreakBrick : public CGameObject {
	float type;
	ULONGLONG count_start;
public:
	CBreakBrick(float x, float y, float type = BREAK_BRICK_TYPE_NORMAL) : CGameObject(x, y) {
		this->type = type;
		count_start = -1;
		point = 10;
		SetState(BREAK_BRICK_STATE_NORMAL);
	};

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	virtual void SetState(int state);
	
	int IsBlocking() { return state != BREAK_BRICK_STATE_TRANSFORM_TO_COIN; }

	float GetType() { return this->type; };
	void createRockObject();
};