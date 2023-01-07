#include "DownBrick.h"

void CDownBrick::Render()
{
	RenderBoundingBox();
}

void CDownBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH*length / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + length*16;
	b = t + BRICK_BBOX_HEIGHT;
}
void CDownBrick::SetState(int state)
{
	CGameObject::SetState(state);
}
