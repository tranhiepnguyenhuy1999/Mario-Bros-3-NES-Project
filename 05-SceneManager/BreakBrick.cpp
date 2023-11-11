#include "BreakBrick.h"
#include "AssetIDs.h"
void CBreakBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = 0;
	switch (state)
	{
	case BREAK_BRICK_STATE_NORMAL:
		aniId = ID_ANI_BREAK_BRICK_NORMAL;
		break;
	case BREAK_BRICK_STATE_TOUCHED:
		if(type == BREAK_BRICK_TYPE_SPECIAL)	aniId = ID_ANI_BREAK_BRICK_TYPE2_TOUCHED;
		break;
	case BREAK_BRICK_STATE_TRANSFORM_TO_COIN:
		aniId = ID_ANI_BREAK_BRICK_TRANSFORM_TO_COIN;
		break;
	default:
		break;
	}
	
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBreakBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BREAK_BRICK_BBOX_WIDTH / 2;
	t = y - BREAK_BRICK_BBOX_HEIGHT / 2;
	r = l + BREAK_BRICK_BBOX_WIDTH;
	b = t + BREAK_BRICK_BBOX_HEIGHT;
}
void CBreakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BREAK_BRICK_STATE_TOUCHED && type != BREAK_BRICK_TYPE_SPECIAL)
	{
		createRockObject();
		isDeleted = true;
	}
	else if (state == BREAK_BRICK_STATE_TRANSFORM_TO_COIN && GetTickCount64() -count_start > BREAK_BRICK_TRANSFORM_TO_COIN_TIMEOUT)
	{
		SetState(BREAK_BRICK_STATE_NORMAL);
	}
}
void CBreakBrick::SetState(int state)
{
	switch (state)
	{
	case BREAK_BRICK_STATE_NORMAL:
		point = 10;
		break;
	case BREAK_BRICK_STATE_TOUCHED:
		if(type == BREAK_BRICK_TYPE_SPECIAL) CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_BUTTON, x, y - BREAK_BRICK_BBOX_HEIGHT);
		break;
	case BREAK_BRICK_STATE_TRANSFORM_TO_COIN:
		if (type == BREAK_BRICK_TYPE_SPECIAL) return;
		count_start = GetTickCount64();
		point = 50;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}
void CBreakBrick::createRockObject() {
		CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_ROCK, x, y, -1.0f, -1.15f);
		CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_ROCK, x, y, 1.0f, -1.0f);
		CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_ROCK, x, y, -1.0f, -0.75f);
		CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_ROCK, x, y, 1.0f, -0.85f);
}