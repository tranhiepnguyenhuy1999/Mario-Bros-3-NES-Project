#pragma once
#include "GameObject.h"

#define CARD_BBOX_WIDTH 16
#define CARD_BBOX_HEIGHT 16

#define CARD_TIMEOUT 250

#define ID_ANI_CARD_MUSHROOM 10100
#define ID_ANI_CARD_MUSHROOM_MOVING 10101

#define ID_ANI_CARD_FLOWER 10102
#define ID_ANI_CARD_FLOWER_MOVING 10103

#define ID_ANI_CARD_STAR 10104
#define ID_ANI_CARD_STAR_MOVING 10105

#define ID_CARD_MUSHROOM 1
#define ID_CARD_FLOWER 2
#define ID_CARD_STAR 3

#define CARD_STATE_TOUCHED 100


class CCard : public CGameObject
{
protected:
	int card_id;
	ULONGLONG loop_start;

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }

	CCard(float x, float y);
	virtual void SetState(int state);

	void handlePlayerTouched() {
		int ani_id = 0;
		switch (card_id)
		{
		case ID_CARD_MUSHROOM:
			ani_id = ID_ANI_CARD_MUSHROOM_MOVING;
			break;
		case ID_CARD_FLOWER:
			ani_id = ID_ANI_CARD_FLOWER_MOVING;
			break;
		case ID_CARD_STAR:
			ani_id = ID_ANI_CARD_STAR_MOVING;
			break;
		default:
			break;
		}
		CGame::GetInstance()->GetCurrentScene()->AddMovingObject(x, y, 0.0f, -0.1f, 0.0f, 0.0f, ani_id, 20000);
	};
};