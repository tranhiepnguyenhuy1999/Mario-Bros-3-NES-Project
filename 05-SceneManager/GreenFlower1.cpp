#include "GreenFlower1.h"
#include "AssetIDs.h"
#include "Pile.h"
#include "debug.h"
CGreenFlower1::CGreenFlower1(float x, float y) :CGameObject(x, y)
{
	ay = 0;
	top = y - FLOWER_BBOX_HEIGHT;
	bot = y;
	loop_start = -1;
	is_after_shooting = false;

	SetState(FLOWER_STATE_STATIC);
}

void CGreenFlower1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FLOWER_BBOX_WIDTH / 2;
	top = y - (FLOWER_BBOX_HEIGHT / 2);
	right = left + FLOWER_BBOX_WIDTH;
	bottom = top + FLOWER_BBOX_HEIGHT;
}

void CGreenFlower1::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CGreenFlower1::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CGreenFlower1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float px, py;
	CGame::GetInstance()->GetCurrentScene()->getPlayerPosition(px, py);

	vy += ay * dt;

	x += vx * dt;
	y += vy * dt;

	if (y < top)
	{
		y = top;
		SetState(FLOWER_STATE_STATIC);
	}
	else if (y > bot)
	{
		y= bot;
		SetState(FLOWER_STATE_STATIC);
	
	}

	if (state==FLOWER_STATE_STATIC)
	{
		if (y == top)
		{
			if (is_after_shooting && (GetTickCount64() - loop_start > FLOWER_AFSHOOT_TIMEOUT)) {
				is_after_shooting = false;
				SetState(FLOWER_STATE_MOVE);
			}
			else if(GetTickCount64() - loop_start > FLOWER_PRESHOOT_TIMEOUT)
			{
				is_after_shooting = true;
				loop_start = GetTickCount64();
				shooting();
			}
		}
		else if (y == bot && (GetTickCount64() - loop_start > FLOWER_LOOP_TIMEOUT))
		{
			SetState(FLOWER_STATE_MOVE);
		}
	}

	CGameObject::Update(dt, coObjects);
}
int CGreenFlower1::getMovingFlowerAniId(int flag) {
	switch (flag)
	{
	case 1:
		return ID_ANI_FLOWER_UP_LEFT_MOVING;
	case 2:
		return ID_ANI_FLOWER_DOWN_LEFT_MOVING;
	case 3:
		return ID_ANI_FLOWER_UP_RIGHT_MOVING;
	case 4:
		return ID_ANI_FLOWER_DOWN_RIGHT_MOVING;
	}

};
int CGreenFlower1::getStaticFlowerAniId(int flag) {
	switch (flag)
	{
	case 1:
		return ID_ANI_FLOWER_UP_LEFT_IDLE;
	case 2:
		return ID_ANI_FLOWER_DOWN_LEFT_IDLE;
	case 3:
		return ID_ANI_FLOWER_UP_RIGHT_IDLE;
	case 4:
		return ID_ANI_FLOWER_DOWN_RIGHT_IDLE;
	}
};
int CGreenFlower1::getFlowerPosition() {
	float px, py;
	CGame::GetInstance()->GetCurrentScene()->getPlayerPosition(px, py);
	if (px < x) {
		if (py < y) return 1; //top-left
		else return 2; //bot-left
	}
	else
	{
		if (py < y) return 3; //top-right
		else return 4; // bot-right
	}
}
void CGreenFlower1::Render()
{
	int flag = getFlowerPosition();
	int aniId;
	if (this->state == FLOWER_STATE_STATIC) {
		aniId = getStaticFlowerAniId(flag);
	}
	else {
		aniId = getMovingFlowerAniId(flag);
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
void CGreenFlower1::SetState(int state)
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
		if (y == top) ay = FLOWER_AXIS_Y;
		else if (y==bot) ay = -FLOWER_AXIS_Y;
		break;
	}
}
void CGreenFlower1::shooting() {
	float px, py;
	CGame::GetInstance()->GetCurrentScene()->getPlayerPosition(px, py);
	CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_FIRE, x, y);
}