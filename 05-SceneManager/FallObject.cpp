#include "FallObject.h"
#include "AssetIDs.h"
#include "KoopaTroopa.h"

CFallObject::CFallObject(float x, float y, float nx, float ny):CGameObject(x, y)
{
	this->ay = FALLOBJECT_GRAVITY;
	vx = nx;
	vy = ny;
}

void CFallObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FALLOBJECT_BBOX_WIDTH / 2;
	top = y - (FALLOBJECT_BBOX_HEIGHT / 2);
	right = left + FALLOBJECT_BBOX_WIDTH;
	bottom = top + FALLOBJECT_BBOX_HEIGHT;
}

void CFallObject::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFallObject::OnCollisionWith(LPCOLLISIONEVENT e)
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
void CFallObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFallObject::Render()
{
	RenderBoundingBox();
}

void CFallObject::SetState(int state)
{
	CGameObject::SetState(state);
}
