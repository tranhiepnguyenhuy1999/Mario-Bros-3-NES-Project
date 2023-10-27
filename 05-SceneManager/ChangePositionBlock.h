#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "Game.h"
#include "PlayScene.h"

#include "Mario.h"

#include "Layer.h"
#include "Camera.h"

#define CHANGE_POSITION_BLOCK_BBOX_WIDTH 16
#define CHANGE_POSITION_BLOCK_BBOX_HEIGHT 16

class CChangePositionBlock : public CGameObject {	
	float next_position_x;
	float next_position_y;
public:
	CChangePositionBlock(float x, float y, float npx, float npy) : CGameObject(x, y) {
		next_position_x = npx;
		next_position_y = npy;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){
		if (CLayer::GetInstance()->IsClosedWindow()) {
			Camera::GetInstance()->setIsFixed(true);
			Camera::GetInstance()->setFixedCamPosition(1968, 432);
			CMario* player = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			player->SetPosition(next_position_x, next_position_y);
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void getNextPositon(float& x, float& y)
	{
		x = next_position_x;
		y = next_position_y;

	}
	void handlePlayerTouched() { CLayer::GetInstance()->closeWindow(); }
};