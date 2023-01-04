#pragma once
#include "debug.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define QUESTIONBRICK_MOVING_SPEED 0.05f

#define ID_ANI_UNTOUCHED_QUESTION_BRICK 10002
#define ID_ANI_TOUCHED_QUESTION_BRICK 10003

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define QUESTION_BRICK_TYPE_NORMAL 1
#define QUESTION_BRICK_TYPE_SPECIAL 2

#define QUESTIONBRICK_STATE_UNTOUCHED 100
#define QUESTIONBRICK_STATE_TOUCHED_1 200
#define QUESTIONBRICK_STATE_TOUCHED_2 300
#define QUESTIONBRICK_STATE_STATIC 400
class CQuestionBrick : public CGameObject {
	float cell;
	float floor;
	float type;
public:
	CQuestionBrick(float x, float y, float type=1) : CGameObject(x, y) {
		state = QUESTIONBRICK_STATE_UNTOUCHED;
		cell = y + 50;
		floor = y;
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {
		//if (state == QUESTIONBRICK_STATE_STATIC) return;
		//if (state == QUESTIONBRICK_STATE_TOUCHED_1) {
		//	y += dt*-QUESTIONBRICK_MOVING_SPEED;
		//	if (y <= cell) {
		//		y = cell;
		//		SetState(QUESTIONBRICK_STATE_TOUCHED_2);
		//	}
		//	return;
		//}
		//if (state == QUESTIONBRICK_STATE_TOUCHED_2) {
		//	y += dt * QUESTIONBRICK_MOVING_SPEED;
		//	if (y >= floor)
		//	{
		//		y = floor;
		//		SetState(QUESTIONBRICK_STATE_STATIC);
		//	}
		//	return;
		//}

	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	float getType() { return this->type; };
	//int IsBlocking() { 
	//	if (state == QUESTIONBRICK_STATE_UNTOUCHED)
	//		return 0;
	//	else return 1;
	//}
};