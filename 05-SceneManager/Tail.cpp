#include "Tail.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "KoopaTroopa.h"
#include "BreakBrick.h"
#include "Button.h"

#include "debug.h"

CTail::CTail(float x, float y, float nx) :CGameObject(x, y)
{
	if (nx < 0)
		vx = -TAIL_ATTACK_SPEED;
	else
		vx = TAIL_ATTACK_SPEED;
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
	else if (dynamic_cast<CBreakBrick*>(e->obj))
		OnCollisionWithBreakBrick(e);
}
void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* obj = dynamic_cast<CGoomba*>(e->obj);

	if (obj->GetState() == GOOMBA_STATE_WALKING)
	{
		obj->SetState(GOOMBA_STATE_DIE_UPSIDE_DOWN);
		CGame::GetInstance()->GetCurrentScene()->AddMovingObject(x, y, 0.0f, 0.0f, 0.0f, 0.0f, ID_ANI_TAIL_TOUCHED_ENEMY, 200);
	}
}
void CTail::OnCollisionWithBreakBrick (LPCOLLISIONEVENT e)
{
	CBreakBrick* obj = dynamic_cast<CBreakBrick*>(e->obj);

	if(obj->GetState() != BREAK_BRICK_STATE_TOUCHED) obj->SetState(BREAK_BRICK_STATE_TOUCHED);
}
void CTail::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* obj = dynamic_cast<CParaGoomba*>(e->obj);

	if (obj->GetState() == PARAGOOMBA_STATE_MOVING)
	{
		obj->SetState(PARAGOOMBA_STATE_DIE_UPSIDE_DOWN);
		CGame::GetInstance()->GetCurrentScene()->AddMovingObject(x, y, 0.0f, 0.0f, 0.0f, 0.0f, ID_ANI_TAIL_TOUCHED_ENEMY, 200);
	}
}
void CTail::OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e)
{
	CKoopaTroopa* item = dynamic_cast<CKoopaTroopa*>(e->obj);

			item->SetState(KOOPATROOPA_STATE_SHELL);
}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((state != TAIL_STATE_DIE) && (GetTickCount64() - count_start >250))
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
