#include "Flower.h"
#include "AssetIDs.h"
CFlower::CFlower(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = -FLOWER_GRAVITY;
	SetState(FLOWER_STATE_ACTIVE);
	yLimit = y - FLOWER_BBOX_HEIGHT;
	die_start = -1;
}

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

		left = x - FLOWER_BBOX_WIDTH / 2;
		top = 368;
		right = left + FLOWER_BBOX_WIDTH;
		bottom = top + FLOWER_BBOX_HEIGHT;
}

void CFlower::OnNoCollision(DWORD dt)
{
	y += vy * dt;
	if (y <= yLimit) {
		y = yLimit;
		vy = FLOWER_GRAVITY;
		return;
	}
	if (y >= yLimit + FLOWER_BBOX_HEIGHT) {
		y = yLimit + FLOWER_BBOX_HEIGHT;
		vy = -FLOWER_GRAVITY;
	}

	//if ((state == FLOWER_STATE_ACTIVE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	//{
	//	SetState(FLOWER_STATE_POW);
	//	return;
	//}
	//if (state == FLOWER_STATE_POW) {
	//	CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_FIRE, x, y, -1);
	//	SetState(FLOWER_STATE_POW);
	//		return;
	//}
};

void CFlower::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CFlower*>(e->obj)) return;

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
	//if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlower::Render()
{
	int aniId = ID_ANI_FOLOWER_UP_LEFT_MOVING;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y +8);
	RenderBoundingBox();
}

void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_ACTIVE:
		die_start = GetTickCount64();
		//vy = -FLOWER_GRAVITY;
		break;
	}
}
