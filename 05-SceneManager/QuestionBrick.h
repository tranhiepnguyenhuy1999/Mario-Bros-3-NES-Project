#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_UNTOUCHED_QUESTION_BRICK 10002
#define ID_ANI_TOUCHED_QUESTION_BRICK 10003

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16


#define QUESTIONBRICK_STATE_UNTOUCHED 100
#define QUESTIONBRICK_STATE_TOUCHED 200

class CQuestionBrick : public CGameObject {
public:
	CQuestionBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	int IsBlocking() { return 0; }
};