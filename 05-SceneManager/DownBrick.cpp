#include "DownBrick.h"

void CDownBrick::Render()
{
	//RenderBoundingBox();
}

void CDownBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + length * BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}
