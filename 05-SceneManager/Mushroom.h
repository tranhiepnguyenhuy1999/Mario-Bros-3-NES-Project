#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_UNTOUCHED_MUSHROOM 10004
#define MUSHROOM_WIDTH 16
#define	MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_STATE_STATIC 100
#define MUSHROOM_STATE_ACTIVE 200
#define MUSHROOM_STATE_DIE 300

class CMushroom : public CGameObject {
	float ax;
	float ay;
public:
	CMushroom(float x, float y);
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};
