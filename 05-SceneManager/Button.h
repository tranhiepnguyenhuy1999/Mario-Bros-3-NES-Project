#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BUTTON 10026
#define ID_ANI_BUTTON_ACTIVE 10027

#define BUTTON_BBOX_WIDTH 10
#define BUTTON_BBOX_HEIGHT 16

#define BUTTON_STATE_ACTIVE	100


class CButton : public CGameObject {
public:
	CButton(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void SetState(int state) {
		CGameObject::SetState(state);
		if (state == BUTTON_STATE_ACTIVE)
		{
			CGame::GetInstance()->GetCurrentScene()->playerTouchedButtonP();
		}
	}

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};