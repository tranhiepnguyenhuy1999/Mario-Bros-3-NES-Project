#pragma once
#include "GameObject.h"

#define FLOWER_GRAVITY 0.04f

#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32

#define GOOMBA_DIE_TIMEOUT 500

#define FLOWER_STATE_ACTIVE 100
#define FLOWER_STATE_POW 200
#define FLOWER_STATE_STATIC 300

#define ID_ANI_FLOWER_UP_LEFT_IDLE 12001
#define ID_ANI_FLOWER_DOWN_LEFT_IDLE 12002
#define ID_ANI_FOLOWER_UP_LEFT_MOVING 12003
#define ID_ANI_FOLOWER_UP_LEFT_MOVING 12004

class CFlower : public CGameObject
{
	float yLimit;
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFlower(float x, float y);
	virtual void SetState(int state);
};