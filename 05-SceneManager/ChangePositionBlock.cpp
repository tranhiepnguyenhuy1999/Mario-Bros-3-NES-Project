#include "ChangePositionBlock.h"

void CChangePositionBlock::Render()
{
	RenderBoundingBox();
}

void CChangePositionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CHANGE_POSITION_BLOCK_BBOX_WIDTH / 2;
	t = y - CHANGE_POSITION_BLOCK_BBOX_HEIGHT / 2;
	r = l + CHANGE_POSITION_BLOCK_BBOX_WIDTH;
	b = t + CHANGE_POSITION_BLOCK_BBOX_HEIGHT;
}