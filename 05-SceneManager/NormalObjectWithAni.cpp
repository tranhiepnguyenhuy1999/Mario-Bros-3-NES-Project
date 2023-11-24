#include "NormalObjectWithAni.h"

void CNormalObjectWithAni::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CNormalObjectWithAni::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 1;
	b = t + 1;
}