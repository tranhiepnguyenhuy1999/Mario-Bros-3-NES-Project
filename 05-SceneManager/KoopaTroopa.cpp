#include "KoopaTroopa.h"

CKoopaTroopa::CKoopaTroopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPATROOPA_GRAVITY;
	count_start = -1;
	SetState(KOOPATROOPA_STATE_WALKING);
}

void CKoopaTroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPATROOPA_STATE_DIE || state== KOOPATROOPA_STATE_ALIVE)
	{
		left = x - KOOPATROOPA_BBOX_WIDTH / 2;
		top = y - (KOOPATROOPA_BBOX_HEIGHT_DIE / 2);
		right = left + KOOPATROOPA_BBOX_WIDTH;
		bottom = top + KOOPATROOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOPATROOPA_BBOX_WIDTH / 2;
		top = y - (KOOPATROOPA_BBOX_HEIGHT/2);
		right = left + KOOPATROOPA_BBOX_WIDTH;
		bottom = top + KOOPATROOPA_BBOX_HEIGHT ;
	}
}

void CKoopaTroopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopaTroopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPATROOPA_STATE_DIE) && (GetTickCount64() - count_start > KOOPATROOPA_DIE_TIMEOUT))
	{
		SetState(KOOPATROOPA_STATE_ALIVE);
		return;
	}
	if ((state == KOOPATROOPA_STATE_ALIVE) && (GetTickCount64() - count_start > KOOPATROOPA_ALIVE_TIMEOUT))
	{
		SetState(KOOPATROOPA_STATE_WALKING);
		y = y + (KOOPATROOPA_BBOX_HEIGHT_DIE/2) - KOOPATROOPA_BBOX_HEIGHT/2 ;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopaTroopa::Render()
{
	int aniId = ID_ANI_KOOPATROOPA_WALKING;
	if (state == KOOPATROOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPATROOPA_DIE;
	}
	if (state == KOOPATROOPA_STATE_ALIVE)
	{
		aniId = ID_ANI_KOOPATROOPA_ALIVE;
	}
	if (state == KOOPATROOPA_STATE_KICKING)
	{
		aniId = ID_ANI_KOOPATROOPA_KICKING;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopaTroopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPATROOPA_STATE_DIE:
		count_start = GetTickCount64();
		y += (KOOPATROOPA_BBOX_HEIGHT - KOOPATROOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPATROOPA_STATE_ALIVE:
		count_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPATROOPA_STATE_WALKING:
		vx = -KOOPATROOPA_WALKING_SPEED;
		break;
	case KOOPATROOPA_STATE_KICKING:
		vx = KOOPATROOPA_KICKING_SPEED;
		break;
	}
}
