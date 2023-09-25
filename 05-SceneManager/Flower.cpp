#include "Flower.h"
#include "AssetIDs.h"
#include "Pile.h"
#include "Camera.h"
#include "debug.h"

CFlower::CFlower(float x, float y) :CGameObject(x, y)
{
	ay = 0;
	top = y - FLOWER_BBOX_HEIGHT;
	bot = y;
	loop_start = -1;
	isWorking = true;
	SetState(FLOWER_STATE_STATIC);
}

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FLOWER_BBOX_WIDTH / 2;
	top = y - (FLOWER_BBOX_HEIGHT / 2);
	right = left + FLOWER_BBOX_WIDTH;
	bottom = top + FLOWER_BBOX_HEIGHT;
}

void CFlower::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CFlower::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float px, py;
	Camera::GetInstance()->getPlayerPosition(px, py);

	vy += ay * dt;

	x += vx * dt;
	y += vy * dt;

	if (!isWorking) {
		if (abs(px - x) > FLOWER_UNWORKING_RANGE) isWorking = true;
		return;
	}

	if (y < top)
	{
		y = top;
		SetState(FLOWER_STATE_STATIC);
	}
	else if (y > bot)
	{
		y = bot;
		SetState(FLOWER_STATE_STATIC);
	}

	if (state == FLOWER_STATE_STATIC)
	{
		if (y == top && (GetTickCount64() - loop_start > FLOWER_ATTACK_TIMEOUT))
		{
			SetState(FLOWER_STATE_MOVE);
		}
		else if (y == bot && abs(px - x) < FLOWER_UNWORKING_RANGE) isWorking = false;

		else if (y == bot && (GetTickCount64() - loop_start > FLOWER_LOOP_TIMEOUT))
		{
			SetState(FLOWER_STATE_MOVE);
		}
	}

	CGameObject::Update(dt, coObjects);
}
void CFlower::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_FLOWER_ATTACKING)->Render(x, y);
	RenderBoundingBox();
}
void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_STATIC:
		loop_start = GetTickCount64();
		ay = 0;
		vy = 0;
		break;
	case FLOWER_STATE_MOVE:
		if (y == top) ay = FLOWER_Y_AXIS;
		else if (y == bot) ay = -FLOWER_Y_AXIS;
		break;
	}
}