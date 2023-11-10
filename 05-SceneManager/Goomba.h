#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.00075f
#define GOOMBA_WALKING_SPEED 0.035f
#define GOOMBA_DIE_BY_TAIL_TOUCHED_SPEED 0.125f
#define GOOMBA_DIE_BY_TAIL_TOUCHED_BOUNCE 0.25f



#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_DIE_UPSIDE_DOWN 300


#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_DIE_UPSIDE_DOWN 6004


class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	bool isActive=false;

	ULONGLONG die_start;
public: 	
	CGoomba(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state==GOOMBA_STATE_WALKING; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	
	virtual void SetState(int state);
	
	virtual void AddPointToUserBoard() {
		CGameObject::AddPointToUserBoard();
		CGame::GetInstance()->GetCurrentScene()->AddStopMovingObjectAxisY(x, y, 0, -0.05f,0,0.00005f, 10200, 5000, false);
	};
};