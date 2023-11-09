#include "ParaGoomba.h"
#include "QuestionBrick.h"
#include "AssetIDs.h"

CParaGoomba::CParaGoomba(float x, float y) :CGameObject(x, y)
{
	point = 100;
	this->ay = PARAGOOMBA_GRAVITY;
	vx = -PARAGOOMBA_SPEED;
	isOnFlatform = false;
	count_start = -1;
	count = 0;
	level = PARAGOOMBA_LEVEL_FLY;
	SetState(PARAGOOMBA_STATE_MOVING);
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARAGOOMBA_STATE_DIE)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - (PARAGOOMBA_BBOX_HEIGHT_DIE / 2);
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - (PARAGOOMBA_BBOX_HEIGHT / 2);
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (!isOnFlatform) isOnFlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (state == PARAGOOMBA_STATE_DIE)
	{
		if(GetTickCount64() - count_start > PARAGOOMBA_LOOP_TIMEOUT)
		this->isDeleted = true;
	}
	else if (level == PARAGOOMBA_LEVEL_NORMAL)
	{
		SetState(PARAGOOMBA_STATE_MOVING);
	}
	else if (state == PARAGOOMBA_STATE_MOVING && (GetTickCount64() - count_start > PARAGOOMBA_LOOP_TIMEOUT))
	{
		SetState(PARAGOOMBA_STATE_JUMP);
	}
	else if (state == PARAGOOMBA_STATE_JUMP)
	{
		if(isOnFlatform) SetState(PARAGOOMBA_STATE_SMALL_JUMP);
	}
	else if (state == PARAGOOMBA_STATE_SMALL_JUMP)
	{
		if (count < PARAGOOMBA_SMALL_JUMP_TIMES)
		{
			if (isOnFlatform)
			{
				vy -= PARAGOOMBA_SMALL_JUMP_DEFLECT_SPEED;
				isOnFlatform = false;
				count++;
			}
		}
		else
		{
			SetState(PARAGOOMBA_STATE_MOVING);
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaGoomba::Render()
{
	int aniId = ID_ANI_PARAGOOMBA_WALKING;
	if (state == PARAGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARAGOOMBA_DIE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	if (level==PARAGOOMBA_LEVEL_FLY)
	{
		CAnimations::GetInstance()->Get(ID_ANI_PARAGOOMBA_WINNG_RIGHT)->Render(x + PARAGOOMBA_BBOX_WIDTH/2, y-PARAGOOMBA_BBOX_HEIGHT/2);
		CAnimations::GetInstance()->Get(ID_ANI_PARAGOOMBA_WINNG_LEFT)->Render(x - PARAGOOMBA_BBOX_WIDTH / 2, y - PARAGOOMBA_BBOX_HEIGHT / 2);
	}
	//RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAGOOMBA_STATE_DIE:
		count_start = GetTickCount64();
		y += (PARAGOOMBA_BBOX_HEIGHT - PARAGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARAGOOMBA_STATE_JUMP:
		isOnFlatform = false;
		vy -= PARAGOOMBA_JUMP_DEFLECT_SPEED;
		break;
	case PARAGOOMBA_STATE_MOVING:
		count = 0;
		count_start = GetTickCount64();
		break;
	case PARAGOOMBA_STATE_SMALL_JUMP:
		break;
	}
}
