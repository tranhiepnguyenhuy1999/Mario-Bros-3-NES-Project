#pragma once
#include "GameObject.h"

class CMovingObject : public CGameObject
{
protected:
	float ax, ay;
	int ani_id;
	int delete_times;

	ULONGLONG die_start;
public:

	CMovingObject(float x, float y, float vx, float vy, float ax = 0, float ay = 0, int ani_id = 0, int delete_times = 1000);
	

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }

	virtual void SetState(int state);
};