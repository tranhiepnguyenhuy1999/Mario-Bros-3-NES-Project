#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"

#define ID_ANI_BRICK 10006
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define DOWNBRICK_STATE_STATIC 100
#define DOWNBRICK_STATE_ONTOP 200

class CDownBrick : public CGameObject {
	float length;

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();

	int IsBlocking() {
		if (state == DOWNBRICK_STATE_STATIC)
			return 0;
		else return 1;
	}

	public:
	CDownBrick(float x, float y, int item) : CGameObject(x, y) {
		state = DOWNBRICK_STATE_STATIC;
		length = item;
	}
	virtual void SetState(int state);
};