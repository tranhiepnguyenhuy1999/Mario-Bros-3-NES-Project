#pragma once
#include "KoopaTroopa.h"


#define ID_ANI_WING 6002

class CParaKoopaTroopa : public CKoopaTroopa
{
protected:
	boolean isOnFlatform;

public:
	CParaKoopaTroopa(float x, float y);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);
	virtual void Render();
};