#include "Tail.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "KoopaTroopa.h"
#include "debug.h"

CTail::CTail(float x, float y) :CGameObject(x, y)
{
	SetState(TAIL_STATE_RELASE);
}
void CTail::Render()
{
	RenderBoundingBox();
}
void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	DebugOut(L"yeah");
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CParaGoomba*>(e->obj))
		OnCollisionWithParaGoomba(e);
	else if (dynamic_cast<CKoopaTroopa*>(e->obj))
		OnCollisionWithKoopaTroopa(e);
}
void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	goomba->SetState(GOOMBA_STATE_DIE);
}
void CTail::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* goomba = dynamic_cast<CParaGoomba*>(e->obj);
	goomba->SetState(GOOMBA_STATE_DIE);
}
void CTail::OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e)
{
	CKoopaTroopa* item = dynamic_cast<CKoopaTroopa*>(e->obj);
	DebugOut(L"yeah");
			item->SetState(KOOPATROOPA_STATE_DIE);
}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((state != TAIL_STATE_DIE) && (GetTickCount64() - count_start >5000))
	{
		count_start = -1;
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TAIL_BBOX_WIDTH / 2;
	t = y - TAIL_BBOX_HEIGHT / 2;
	r = l + TAIL_BBOX_WIDTH;
	b = t + TAIL_BBOX_HEIGHT;
}
void CTail::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TAIL_STATE_RELASE:
		count_start = GetTickCount64();
		break;
	}
}
