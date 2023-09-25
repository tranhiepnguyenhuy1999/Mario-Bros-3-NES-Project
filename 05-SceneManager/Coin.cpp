#include "Coin.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani_id = ID_ANI_COIN;
	if (type == COIN_TYPE_STATIC)
		ani_id = ID_ANI_COIN_STATIC;
	animations->Get(ani_id)->Render(x, y);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}