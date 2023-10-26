#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define CHANGE_POSITION_BLOCK_BBOX_WIDTH 16
#define CHANGE_POSITION_BLOCK_BBOX_HEIGHT 16

class CChangePositionBlock : public CGameObject {	
	float next_position_x;
	float next_position_y;

public:
	CChangePositionBlock(float x, float y, float npx, float npy) : CGameObject(x, y) {
		next_position_x = npx;
		next_position_y = npy;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void getNextPositon(float& x, float& y)
	{
		x = next_position_x;
		y = next_position_y;

	}
};