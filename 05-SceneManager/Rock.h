#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ROCK_SPEED	0.07f
#define ROCK_BOUNCE_SPEED	0.35f
#define ROCK_GRAVITY	0.00075f

#define ID_ANI_ROCK 10025

#define	TAIL_BBOX_WIDTH 4
#define TAIL_BBOX_HEIGHT 8

class CRock : public CGameObject {
	float ax, ay;

	boolean isOnGround;
public:
	CRock(float x, float y, float nx, float ny);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);
};
