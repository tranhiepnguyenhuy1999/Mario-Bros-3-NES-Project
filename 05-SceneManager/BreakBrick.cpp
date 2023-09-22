#include "BreakBrick.h"
#include "AssetIDs.h"
void CBreakBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_UNTOUCHED_QUESTION_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CBreakBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}
void CBreakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BREAK_BRICK_STATE_TOUCHED)
	{
		createRockObject();
		isDeleted = true;
		return;
	}
}
void CBreakBrick::SetState(int state)
{
	CGameObject::SetState(state);
}
void CBreakBrick::createRockObject() {
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_ROCK, x, y, -1, -1.15);
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_ROCK, x, y, 1, -1);
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_ROCK, x, y, -1, -0.75f);
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_ROCK, x, y, 1, -0.85f);
}