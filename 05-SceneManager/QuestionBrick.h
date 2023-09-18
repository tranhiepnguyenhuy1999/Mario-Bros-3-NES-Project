#pragma once
#include "debug.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define QUESTIONBRICK_MOVING_BOUNCE 0.0005f
#define QUESTIONBRICK_MOVING_BOUNCE_RANGE	3.0f

#define ID_ANI_UNACTIVE_QUESTION_BRICK 10002
#define ID_ANI_ACTIVE_QUESTION_BRICK 10003

#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define QUESTION_BRICK_TYPE_NORMAL 1
#define QUESTION_BRICK_TYPE_SPECIAL 2

#define QUESTIONBRICK_STATE_UNACTIVE 100
#define QUESTIONBRICK_STATE_TOUCHED 200
#define QUESTIONBRICK_STATE_ACTIVE 300
class CQuestionBrick : public CGameObject {
	float type;
	float range;
	float ay;

public:
	CQuestionBrick(float x, float y, float type = 1);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	float getType() { return this->type; };
};