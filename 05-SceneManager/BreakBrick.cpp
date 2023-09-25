#include "BreakBrick.h"
#include "AssetIDs.h"
void CBreakBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(type == BREAK_BRICK_TYPE_SPECIAL && state== BREAK_BRICK_STATE_TOUCHED)
		animations->Get(ID_ANI_BREAK_BRICK_TYPE2_TOUCHED)->Render(x, y);
	else 
		animations->Get(ID_ANI_BREAK_BRICK_UNTOUCHED)->Render(x, y);
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
		return;
	}
}
void CBreakBrick::SetState(int state)
{
	if (state == BREAK_BRICK_STATE_TOUCHED && type == BREAK_BRICK_TYPE_SPECIAL)
	{
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_BUTTON, x, y - BREAK_BRICK_BBOX_HEIGHT);
	}

	CGameObject::SetState(state);
}
void CBreakBrick::createRockObject() {
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_ROCK, x, y, -1, -1.15);
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_ROCK, x, y, 1, -1);
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_ROCK, x, y, -1, -0.75f);
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_ROCK, x, y, 1, -0.85f);
}