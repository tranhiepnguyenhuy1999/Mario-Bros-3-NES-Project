#include "Fire.h"

CFire::CFire(float x, float y, float vx) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	SetState(FIRE_STATE_RELASE);
	yLimit = y - 16;
	xLimit = x;
	this->rect = vx;

}
void CFire::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->state == FIRE_STATE_DIE)
	{
		animations->Get(ID_ANI_UNTOUCHED_MUSHROOM)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_UNTOUCHED_MUSHROOM)->Render(x, y);
	}
	//RenderBoundingBox();
}
void CFire::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	if (y <= yLimit) {
		y = yLimit;
		SetState(FIRE_STATE_ACTIVE);
		return;
	}
	if (vy != 0) {
		vx = 0;
		if (x + FIRE_WIDTH <= xLimit) x = xLimit - FIRE_WIDTH;
	}
	if (vy == 0) {
		vx = rect * FIRE_WALKING_SPEED;
	}
};

void CFire::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFire*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((state == FIRE_STATE_DIE))
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
void CFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIRE_BBOX_WIDTH / 2;
	t = y - FIRE_BBOX_HEIGHT / 2;
	r = l + FIRE_BBOX_WIDTH;
	b = t + FIRE_BBOX_HEIGHT;
}
void CFire::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	}
}
