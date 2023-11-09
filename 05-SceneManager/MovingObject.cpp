#include "MovingObject.h"
#include "debug.h"

CMovingObject::CMovingObject(float x, float y, float vx, float vy, float ax, float ay, int ani_id, int delete_times):CGameObject(x, y)
{
	this->ax = ax;
	this->ay = ay;

	this->vx = vx;
	this->vy = vy;
	this->ani_id = ani_id;
	this->delete_times = delete_times;
	die_start = GetTickCount64();
}

void CMovingObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 1;
	top = y - 1;
	right = left + 1;
	bottom = top + 1;
}
void CMovingObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;

	x += vx * dt;
	y += vy * dt;

	if (GetTickCount64() - die_start > delete_times)
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
}


void CMovingObject::Render()
{
	CAnimations::GetInstance()->Get(ani_id)->Render(x, y);
	RenderBoundingBox();
}

void CMovingObject::SetState(int state)
{
	CGameObject::SetState(state);
}
