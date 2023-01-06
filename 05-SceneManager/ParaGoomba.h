#pragma once
#include "GameObject.h"

#define PARAGOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.03f
#define PARAGOOMBA_KICKING_SPEED 0.2f
#define PARAGOOMBA_JUMP_SPEED 0.07f

#define PARAGOOMBA_MAX_Y 50

#define PARAGOOMBA_BBOX_WIDTH 15
#define PARAGOOMBA_BBOX_HEIGHT 26
#define PARAGOOMBA_BBOX_HEIGHT_DIE 16

#define PARAGOOMBA_DIE_TIMEOUT 3000
#define PARAGOOMBA_ALIVE_TIMEOUT 2000
#define PARAGOOMBA_JUMP_TIMEOUT 500

#define PARAGOOMBA_STATE_WALKING 100
#define PARAGOOMBA_STATE_DIE 200
#define PARAGOOMBA_STATE_ALIVE 300
#define PARAGOOMBA_STATE_KICKING 400
#define PARAGOOMBA_STATE_JUMP 500
#define PARAGOOMBA_STATE_RELEASE_JUMP 600

#define ID_ANI_PARAGOOMBA_WALKING 7000
#define ID_ANI_PARAGOOMBA_DIE 7001
#define ID_ANI_PARAGOOMBA_KICKING 7002
#define ID_ANI_PARAGOOMBA_ALIVE 7003

class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	float type;

	ULONGLONG count_start;
	ULONGLONG ready_jump_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);
};