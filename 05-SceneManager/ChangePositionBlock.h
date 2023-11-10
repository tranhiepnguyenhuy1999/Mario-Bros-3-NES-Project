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
#define CHANGE_POSITION_BLOCK_BBOX_HEIGHT 8

class CChangePositionBlock : public CGameObject {	
	float next_position_x, next_position_y;
	float next_cam_l, next_cam_t;
	float dest_position_x, dest_position_y;

	bool isDown;
	bool isActive;
	bool isCamFixed;

public:
	CChangePositionBlock(float x, float y, bool is_down, float npx, float npy, float ncl, float nct, bool is_fixed, float dpx, float dpy) : CGameObject(x, y) {
		isActive = false;
		isDown = is_down;

		next_position_x = npx;
		next_position_y = npy;
		
		next_cam_l = ncl;
		next_cam_t = nct;
		isCamFixed = is_fixed;

		dest_position_x = dpx;
		dest_position_y = dpy;
	}
	void Render();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (isActive && CLayer::GetInstance()->IsClosedWindow()) {
			Camera::GetInstance()->setIsFixed(isCamFixed, isCamFixed);
			Camera::GetInstance()->setFixedCamPosition(next_cam_l, next_cam_t);
			CMario* player = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			player->SetPosition(next_position_x, next_position_y);
		}
		else if (isActive)
		{
			float px, py;
			CMario* player = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			Camera::GetInstance()->getPlayerPosition(px, py);
			
			if (dest_position_x < px) {

				if (isDown)
				{
					if (py < dest_position_y) return;
				}
				else
				{
					if (py > dest_position_y) return;
				}
				player->SetState(MARIO_STATE_OUT_PILE);
				isActive = false;
			}
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void getNextPositon(float& x, float& y)
	{
		x = next_position_x;
		y = next_position_y;

	}
	void handlePlayerTouched() { 
		CLayer::GetInstance()->closeWindow();
		isActive = true; }
};