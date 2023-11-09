#include "Card.h"

CCard::CCard(float x, float y) :CGameObject(x, y)
{
	loop_start = -1;
	card_id = 1;
	state = 0;
}

void CCard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CARD_BBOX_WIDTH / 2;
	top = y - CARD_BBOX_HEIGHT / 2;
	right = left + CARD_BBOX_WIDTH;
	bottom = top + CARD_BBOX_HEIGHT;
}

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state==CARD_STATE_TOUCHED)
	{
		return;
	}
	else if (GetTickCount64() - loop_start > CARD_TIMEOUT)
	{
		if (card_id > 2) card_id = 1;
		else card_id += 1;
		loop_start = GetTickCount64();
	}
}


void CCard::Render()
{
	int aniId = 0;
	switch (card_id)
	{
	case ID_CARD_MUSHROOM:
		aniId = ID_ANI_CARD_MUSHROOM;
		break;
	case ID_CARD_FLOWER:
		aniId = ID_ANI_CARD_FLOWER;
		break;
	case ID_CARD_STAR:
		aniId = ID_ANI_CARD_STAR;
		break;
	default:
		aniId = ID_ANI_CARD_MUSHROOM;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CCard::SetState(int state)
{
	CGameObject::SetState(state);
}
