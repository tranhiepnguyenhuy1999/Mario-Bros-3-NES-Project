#pragma once
#include "GameObject.h"

#define FLOWER_Y_AXIS 0.0001f

#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32

#define FLOWER_SHOOTING_RANGE 100.0f

#define FLOWER_PRESHOOT_TIMEOUT 1500
#define FLOWER_AFSHOOT_TIMEOUT 750
#define FLOWER_LOOP_TIMEOUT 3000

#define FLOWER_STATE_MOVE 100
#define FLOWER_STATE_STATIC 200

#define ID_ANI_FLOWER_UP_LEFT_IDLE 19001
#define ID_ANI_FLOWER_DOWN_LEFT_IDLE 19002

#define ID_ANI_FLOWER_UP_LEFT_MOVING 19003
#define ID_ANI_FLOWER_DOWN_LEFT_MOVING 19004

#define ID_ANI_FLOWER_UP_RIGHT_IDLE 19005
#define ID_ANI_FLOWER_DOWN_RIGHT_IDLE 19006

#define ID_ANI_FLOWER_UP_RIGHT_MOVING 19007
#define ID_ANI_FLOWER_DOWN_RIGHT_MOVING 19008

class CGreenFlower1 : public CGameObject
{

protected:
	float ay;
	float top;
	float bot;
	boolean is_after_shooting;
	float ani_pow_id;

	ULONGLONG loop_start;

	int getMovingFlowerAniId(int flag);
	int getStaticFlowerAniId(int flag);

	int getFlowerPosition();
	int getPlayerPosition();
	float translateToPercent(float data, boolean isXAxis);
	void shooting();

public:
	CGreenFlower1(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);
};