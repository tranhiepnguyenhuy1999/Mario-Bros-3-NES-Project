#pragma once
#include "GameObject.h"

#define PARAGOOMBA_GRAVITY 0.00035f
#define PARAGOOMBA_SPEED 0.03f

#define PARAGOOMBA_SMALL_JUMP_DEFLECT_SPEED 0.05f
#define PARAGOOMBA_JUMP_DEFLECT_SPEED 0.15f

#define PARAGOOMBA_SMALL_JUMP_TIMES 3

#define PARAGOOMBA_BBOX_WIDTH 16
#define PARAGOOMBA_BBOX_HEIGHT 14
#define PARAGOOMBA_BBOX_HEIGHT_DIE 7

#define PARAGOOMBA_LOOP_TIMEOUT 750

#define PARAGOOMBA_STATE_MOVING 100	
#define PARAGOOMBA_STATE_JUMP 200
#define PARAGOOMBA_STATE_SMALL_JUMP 300
#define PARAGOOMBA_STATE_DIE 400

#define ID_ANI_PARAGOOMBA_WALKING 6000
#define ID_ANI_PARAGOOMBA_DIE 6001
#define ID_ANI_PARAGOOMBA_WINNG_RIGHT 6002
#define ID_ANI_PARAGOOMBA_WINNG_LEFT 6003

#define	PARAGOOMBA_LEVEL_FLY	2
#define	PARAGOOMBA_LEVEL_NORMAL	1


class CParaGoomba : public CGameObject
{
protected:
	float ay;
	int count;
	int level;

	boolean isOnFlatform;

	ULONGLONG count_start;

public:
	CParaGoomba(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);

	int getLevel() { return level; }
	void setLevel(int new_level) { level=new_level; }

};