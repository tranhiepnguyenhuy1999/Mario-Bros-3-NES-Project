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
void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((state == MUSHROOM_STATE_DIE))
	{
		isDeleted = true;
		return;
	}

	vy += ay * dt;
	vx += ax * dt;

	//if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
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
