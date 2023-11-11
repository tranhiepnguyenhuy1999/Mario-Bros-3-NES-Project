#include "QuestionBrick.h"
#include "AssetIDs.h"
#include "Mario.h"

CQuestionBrick::CQuestionBrick(float x, float y, float type, int state) : CGameObject(x, y) {

	this->type = type;
	range = y - QUESTIONBRICK_MOVING_BOUNCE_RANGE;
	SetState(state);
}
void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniID = ID_ANI_UNACTIVE_QUESTION_BRICK;
	if (this->state != QUESTIONBRICK_STATE_UNACTIVE) aniID = ID_ANI_ACTIVE_QUESTION_BRICK; animations->Get(aniID)->Render(x, y);
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}
void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	y += vy * dt;
	if (state== QUESTIONBRICK_STATE_TOUCHED)
	{
		if (y < range) {
			y = range; 
			ay = -ay;
			vy = 0;
		}
		else if(y > range + QUESTIONBRICK_MOVING_BOUNCE_RANGE)
		{
			y = range + QUESTIONBRICK_MOVING_BOUNCE_RANGE;
			SetState(QUESTIONBRICK_STATE_ACTIVE);
		}
	}
	else if (state == QUESTIONBRICK_STATE_ACTIVE)
	{
		if (type == QUESTION_BRICK_TYPE_SPECIAL)
		{
			int plevel;
			CGame::GetInstance()->GetCurrentScene()->getPlayerLevel(plevel);
			if (plevel == MARIO_LEVEL_RACOON)
			{
				CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_MUSHROOM, x, y, (float)nx, 0.0f, NULL, 1);
			}
			else if (plevel == MARIO_LEVEL_BIG)
			{
				CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_LEAF, x, y);
			}
			else
			{
				CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_MUSHROOM, x, y, (float)nx, 0.0f, NULL, 0);
			}
			CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_ACTIVE_QUESTIONBRICK, x, y);

			this->Delete();
		}
	}

	CGameObject::Update(dt, coObjects);
}
void CQuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case  QUESTIONBRICK_STATE_UNACTIVE:
		ay = 0;
		vy = 0;
		break;
	case  QUESTIONBRICK_STATE_TOUCHED:
		ay = -QUESTIONBRICK_MOVING_BOUNCE;
		if (type == 1)
		{
			CGame::GetInstance()->GetCurrentScene()->CreateNewObject(OBJECT_TYPE_SMALLCOIN, x, y - 16);
			UserInfo::GetInstance()->updateProps(ID_PROPS_COIN, +1);
		}
		break;
	case  QUESTIONBRICK_STATE_ACTIVE:
		ay = 0;
		vy = 0;
		break;
	}
}