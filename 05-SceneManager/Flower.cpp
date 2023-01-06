#include "Flower.h"
#include "AssetIDs.h"
#include "Pile.h"
#include "debug.h"
CFlower::CFlower(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	SetState(FLOWER_STATE_ACTIVE);
	yLimit = y - FLOWER_BBOX_HEIGHT;
	loop_start = -1;
}

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLOWER_STATE_ONBOTTOM)
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
	else {
	
		left = x - FLOWER_BBOX_WIDTH / 2;
		top = y	- (FLOWER_BBOX_HEIGHT/2);
		right = left + FLOWER_BBOX_WIDTH;
		bottom = top + FLOWER_BBOX_HEIGHT;
	}
}

void CFlower::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CFlower::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CPile*>(e->obj)) return;

	//if (e->ny != 0)
	//{
	//	vy = 0;
	//}
	//else if (e->nx != 0)
	//{
	//	vx = -vx;
	//}

	//y += vy;
	//if (y <= yLimit) {
	//	y = yLimit;
	//	vy = FLOWER_GRAVITY;
	//	return;
	//}
	//if (y >= yLimit + FLOWER_BBOX_HEIGHT) {
	//	y = yLimit + FLOWER_BBOX_HEIGHT;
	//	vy = -FLOWER_GRAVITY;
	//}
}

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L">>> Count time >>> %d \n", GetTickCount64() - loop_start);
	float px, py, nx, ny;
	CGame::GetInstance()->GetCurrentScene()->getPlayerPosition(px, py);

	if (px >= x) {
		nx = 1;
	}
	else nx = -1;
	if (py >= y) {
		ny = 1;
	}
	else ny = -1;

	if ((state == FLOWER_STATE_ONTOP) && (GetTickCount64() - loop_start > FLOWER_LOOP_TIMEOUT))
	{
		SetState(FLOWER_STATE_POW);
		return;
	}
	if ((state == FLOWER_STATE_POW) && (GetTickCount64() - loop_start > FLOWER_LOOP_TIMEOUT))
	{

	 	CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_FIRE, x, y);
		SetState(FLOWER_STATE_ACTIVE);
		return;
	}
	if ((state == FLOWER_STATE_ONBOTTOM) && (GetTickCount64() - loop_start > FLOWER_BOTTOM_LOOP_TIMEOUT))
	{
		if (px >= x - 50 && px < x + 50) return;
		SetState(FLOWER_STATE_ACTIVE);
		return;
	}
	if (y < yLimit)
	{
		SetState(FLOWER_STATE_ONTOP);
	}else if (y > yLimit + FLOWER_BBOX_HEIGHT)
	{
		SetState(FLOWER_STATE_ONBOTTOM);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlower::Render()
{
	int aniId = ID_ANI_FOLOWER_UP_LEFT_MOVING;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_POW:
		break;
	case FLOWER_STATE_ONTOP:
		y = yLimit;
		loop_start = GetTickCount64();
		vy = 0;
		break;
	case FLOWER_STATE_ONBOTTOM:
		y = yLimit + FLOWER_BBOX_HEIGHT;
		loop_start = GetTickCount64();
		vy = 0;
		break;
	case FLOWER_STATE_ACTIVE:
		if (y <= yLimit)
		{
			vy = FLOWER_SPEED;
		}
		else if (y >= yLimit + FLOWER_BBOX_HEIGHT)
		{
			vy = -FLOWER_SPEED;
		}
		break;
	}
}
