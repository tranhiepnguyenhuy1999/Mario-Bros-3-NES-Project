#include "ParaKoopaTroopa.h"
#include "DownBrick.h"
#include "QuestionBrick.h"
#include "Goomba.h"
#include "Mario.h"

CParaKoopaTroopa::CParaKoopaTroopa(float x, float y) :CKoopaTroopa(x, y)
{
	nx = 1;
	isOnFlatform = false;
	isHaveFallObj = false;
	SetState(PARA_KOOPATROOPA_STATE_JUMP);
}
void CParaKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	
	if (state == PARA_KOOPATROOPA_STATE_JUMP) {
		if (isOnFlatform) {
			vy -= PARA_KOOPATROOPA_JUMP_DEFLECT_SPEED;
			isOnFlatform = false;
		}
	}
	else {
		CKoopaTroopa::Update(dt, coObjects);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParaKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (!isOnFlatform) isOnFlatform = true;
	}

	CKoopaTroopa::OnCollisionWith(e);
}


void CParaKoopaTroopa::Render()
{
	CKoopaTroopa::Render();

	if(state == PARA_KOOPATROOPA_STATE_JUMP) CAnimations::GetInstance()->Get(ID_ANI_WING)->Render(x + KOOPATROOPA_BBOX_WIDTH/2, y - KOOPATROOPA_BBOX_HEIGHT/4);
}

void CParaKoopaTroopa::SetState(int state)
{
	CKoopaTroopa::SetState(state);

	//switch (state)
	//{

	//}
}
