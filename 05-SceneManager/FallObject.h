#pragma once
#include "GameObject.h"

#define FALLOBJECT_BBOX_WIDTH 8
#define FALLOBJECT_BBOX_HEIGHT 8

#define FALLOBJECT_GRAVITY	0.001f
#define FALLOBJECT_MAX_GRAVITY 0.1f

class CFallObject : public CGameObject
{
protected:
	float ay;

public:
	CFallObject(float x, float y, float nx, float ny=0);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);
	
	boolean isFalling() {
		return abs(vy) > FALLOBJECT_MAX_GRAVITY;
	}
};