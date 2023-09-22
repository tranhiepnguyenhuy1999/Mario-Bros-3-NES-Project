#pragma once
#include "GameObject.h"

#define FLOWER_Y_AXIS 0.0001f

#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32

#define FLOWER_UNWORKING_RANGE 50.0f

#define FLOWER_ATTACK_TIMEOUT 1500
#define FLOWER_LOOP_TIMEOUT 3000

#define FLOWER_STATE_MOVE 100
#define FLOWER_STATE_STATIC 200

#define ID_ANI_FLOWER_ATTACKING 19009

class CFlower : public CGameObject
{

protected:
	float ay;
	float top;
	float bot;

	boolean isWorking;

	ULONGLONG loop_start;

public:
	CFlower(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);
};