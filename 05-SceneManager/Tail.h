#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define TAIL_ATTACK_SPEED 0.07f

#define TAIL_WIDTH 4
#define	TAIL_BBOX_WIDTH 2
#define TAIL_BBOX_HEIGHT 8

#define TAIL_STATE_RELASE 100
#define TAIL_STATE_DIE 200

#define ID_ANI_TAIL_TOUCHED_ENEMY 10300


class CTail : public CGameObject {
	ULONGLONG count_start;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBreakBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
public:
	CTail(float x, float y, float nx);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);
};
