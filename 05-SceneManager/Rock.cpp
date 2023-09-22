#include "Rock.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "KoopaTroopa.h"
#include "BreakBrick.h"
#include "debug.h"

CRock::CRock(float x, float y, float nx, float ny) :CGameObject(x, y)
{
	vx = nx*ROCK_SPEED;
	vy = ny*ROCK_BOUNCE_SPEED;
	ay = ROCK_GRAVITY;
	isOnGround = false;
}
void CRock::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_ROCK)->Render(x, y);
	//RenderBoundingBox();
}
void CRock::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CRock::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		isOnGround = true;
	}
}
void CRock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (isOnGround)
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CRock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TAIL_BBOX_WIDTH / 2;
	t = y - TAIL_BBOX_HEIGHT / 2;
	r = l + TAIL_BBOX_WIDTH;
	b = t + TAIL_BBOX_HEIGHT;
}
void CRock::SetState(int state)
{
	CGameObject::SetState(state);
}
