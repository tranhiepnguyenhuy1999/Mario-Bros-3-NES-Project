#include "Leaf.h"
CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	SetState(LEAF_STATE_RELASE);
}
void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniID = ID_ANI_UNTOUCHED_LEAF_LEFT;
	if (vx > 0) aniID = ID_ANI_UNTOUCHED_LEAF_RIGHT;
	animations->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
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

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((state == LEAF_STATE_DIE))
	{
		isDeleted = true;
		return;
	}
	if ((state != LEAF_STATE_DIE) && (GetTickCount64() - count_start > 1000))
	{
		SetState(LEAF_STATE_MOVING_TURN);
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}
void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case LEAF_STATE_RELASE:
		count_start = GetTickCount64();
		vx = LEAF_WALKING_SPEED;
		vy = LEAF_FALL_SPEED;
		break;
	case LEAF_STATE_MOVING_TURN:
		count_start = GetTickCount64();
		vx = -vx;
		break;
	}
}
