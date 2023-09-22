#pragma once
#include "debug.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BREAK_BRICK_MOVING_SPEED 0.05f

#define ID_ANI_UNTOUCHED_QUESTION_BRICK 10024
#define ID_ANI_TOUCHED_QUESTION_BRICK 10006	

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define QUESTION_BRICK_TYPE_NORMAL 1
#define QUESTION_BRICK_TYPE_SPECIAL 2

#define BREAK_BRICK_STATE_TOUCHED 100

class CBreakBrick : public CGameObject {
	float type;

public:
	CBreakBrick(float x, float y, float type = 1) : CGameObject(x, y) {
		this->type = type;
	};

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	virtual void SetState(int state);

	float getType() { return this->type; };
	void createRockObject();
};