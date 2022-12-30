#include "Mushroom.h"

CMushroom::CMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	SetState(MUSHROOM_STATE_STATIC);
}
void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->state == MUSHROOM_STATE_DIE)
	{
		animations->Get(ID_ANI_UNTOUCHED_MUSHROOM)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_UNTOUCHED_MUSHROOM)->Render(x, y);
	}
	//RenderBoundingBox();
}
void CMushroom::Update(DWORD dt)
{
	if ((state == MUSHROOM_STATE_DIE))
	{
		isDeleted = true;
		return;
	}

}
void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}
void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_STATIC:
		vx = 0;
		vy = 0;
		ay = 0;
		ax = 0;
		break;
	case MUSHROOM_STATE_ACTIVE:
		y += y;
		vx = 0;
		vy = 0;
		ax = MUSHROOM_WALKING_SPEED;
		ay = -MUSHROOM_GRAVITY;
		break;
	case MUSHROOM_STATE_DIE:
		vx = 0;
		vy = 0;
		ay = 0;
		ax = 0;
		break;
	}
}
