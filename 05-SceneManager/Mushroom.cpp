#include "Mushroom.h"
CMushroom::CMushroom(float x, float y, int obj_type, float vx) :CGameObject(x, y)
{
	if (obj_type == MUSHROOM_TYPE_GREEN) point = 1;
	else point = 1000;
	range = y - MUSHROOM_BBOX_HEIGHT;
	type = obj_type;

	SetState(MUSHROOM_STATE_RELASE);
}
void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = 0;

	if (type == MUSHROOM_TYPE_RED)
		aniId = ID_ANI_MUSHROOM;
	else if (type== MUSHROOM_TYPE_GREEN)
		aniId = ID_ANI_MUSHROOM_GREEN;

	animations->Get(aniId)->Render(x, y);
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
	vy += ay * dt;

	if (state == MUSHROOM_STATE_DIE)
	{
		isDeleted = true;
		return;
	}

	if (state == MUSHROOM_STATE_RELASE && y < range ) {
		y = range;
		SetState(MUSHROOM_STATE_MOVING);
		return;
	}

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
	case MUSHROOM_STATE_RELASE:
		ay = 0;
		vx = 0;
		vy = -MUSHROOM_SPEED;
		break;
	case MUSHROOM_STATE_MOVING:
		ay = MUSHROOM_GRAVITY;
		vy = 0;
		vx = -MUSHROOM_SPEED;
		break;
	}
}
