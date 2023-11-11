#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define MUSHROOM_GRAVITY 0.005f
#define MUSHROOM_SPEED 0.045f
#define MUSHROOM_BOUNCE_SPEED 0.05f


#define ID_ANI_MUSHROOM 10004
#define ID_ANI_MUSHROOM_GREEN 10028


#define MUSHROOM_WIDTH 16
#define	MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_STATE_RELASE 100
#define MUSHROOM_STATE_MOVING 200
#define MUSHROOM_STATE_DIE 300

#define MUSHROOM_TYPE_RED 0
#define MUSHROOM_TYPE_GREEN 1 


class CMushroom : public CGameObject {
	float ay;
	float range;

	int type;
public:
	CMushroom(float x, float y, int obj_type, float vx);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);
};
