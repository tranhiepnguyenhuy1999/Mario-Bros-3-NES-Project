#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define FIRE_GRAVITY 0.07f
#define FIRE_WALKING_SPEED 0.07f

#define ID_ANI_UNTOUCHED_MUSHROOM 12005
#define FIRE_WIDTH 16
#define	FIRE_BBOX_WIDTH 16
#define FIRE_BBOX_HEIGHT 16

#define FIRE_STATE_RELASE 100
#define FIRE_STATE_ACTIVE 200
#define FIRE_STATE_DIE 300

class CFire : public CGameObject {
	float ax;
	float ay;
	float yLimit;
	float xLimit;
	float rect;
public:
	CFire(float x, float y, float vx);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);
};


