#include "KoopaTroopa.h"
#include "DownBrick.h"
#include "QuestionBrick.h"
#include "Goomba.h"
#include "Mario.h"

CKoopaTroopa::CKoopaTroopa(float x, float y, int obj_type) :CGameObject(x, y)
{
	point = 100;
	type = obj_type;

	this->ay = KOOPATROOPA_GRAVITY;
	count_start = -1;
	vx = -KOOPATROOPA_SPEED;
	nx = -1;

	isDie = false;
	isHaveFallObj = true;

	fall_object = NULL;

	SetState(KOOPATROOPA_STATE_MOVING);
}

void CKoopaTroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDie)
	{
		left = x - KOOPATROOPA_BBOX_WIDTH / 2;
		top = y - (KOOPATROOPA_BBOX_HEIGHT_SHELL / 2);	
		right = left + KOOPATROOPA_BBOX_WIDTH;
		bottom = top + KOOPATROOPA_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPATROOPA_BBOX_WIDTH / 2;
		top = y - (KOOPATROOPA_BBOX_HEIGHT/2);
		right = left + KOOPATROOPA_BBOX_WIDTH;
		bottom = top + KOOPATROOPA_BBOX_HEIGHT ;
	}
}

void CKoopaTroopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = -vx;
		nx = -nx;
	}
	if (dynamic_cast<CQuestionBrick*>(e->obj))OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))OnCollisionWithGoomba(e);
}
void CKoopaTroopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	if (state != KOOPATROOPA_STATE_SHELL_MOVING) return;

	CGoomba* obj = dynamic_cast<CGoomba*>(e->obj);

	if (obj->GetState() != GOOMBA_STATE_DIE)
	{
		obj->SetState(GOOMBA_STATE_DIE_UPSIDE_DOWN);
		CGame::GetInstance()->GetCurrentScene()->AddMovingObject(x, y, 0.0f, 0.0f, 0.0f, 0.0f, 10300, 200);
	}
}
void CKoopaTroopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	if (state != KOOPATROOPA_STATE_SHELL_MOVING) return;
	CQuestionBrick* obj = dynamic_cast<CQuestionBrick*>(e->obj);
	obj->SetState(QUESTIONBRICK_STATE_TOUCHED);
}
void CKoopaTroopa::OnCollisionWithDownBrick(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
		vy = 0;
}
void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	
	updateState();

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopaTroopa::updateState()
{
	if (!isDie && isHaveFallObj)
	{
		if (!fall_object)
		{
			createFallObject();
		}
		else {
			if (fall_object->isFalling())
			{
				SetState(KOOPATROOPA_STATE_TURN);
				SetState(KOOPATROOPA_STATE_MOVING);
			}
		}
	}
	else if (state != KOOPATROOPA_STATE_SHELL_MOVING)
	{
		if (isDie && (GetTickCount64() - count_start > KOOPATROOPA_DIE_TIMEOUT))
		{
			SetState(KOOPATROOPA_STATE_ALIVE);
			SetState(KOOPATROOPA_STATE_MOVING);
		}
		else if (isDie && (GetTickCount64() - count_start > KOOPATROOPA_ALIVE_TIMEOUT))
		{
			SetState(KOOPATROOPA_STATE_SHELL_ALIVE);
		}
	}
}

void CKoopaTroopa::Render()
{
	int aniId = ID_ANI_KOOPATROOPA_WALKING_LEFT;
	if (isDie)
	{
		switch (state)
		{
			case KOOPATROOPA_STATE_SHELL:
			case KOOPATROOPA_STATE_SHELL_PICK_UP:
				aniId = ID_ANI_KOOPATROOPA_SHELL;
				break;
			case KOOPATROOPA_STATE_SHELL_ALIVE:
				aniId = ID_ANI_KOOPATROOPA_ALIVE;
				break;
		default:
			aniId = ID_ANI_KOOPATROOPA_KICKING;
			break;
		}
	}
	else if (vx > 0) {
		aniId = ID_ANI_KOOPATROOPA_WALKING_RIGHT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopaTroopa::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPATROOPA_STATE_MOVING:
		isDie = false;
		break;
	case KOOPATROOPA_STATE_SHELL:
		removeFalObj();
		if (!isDie)
		{
			y += (KOOPATROOPA_BBOX_HEIGHT - KOOPATROOPA_BBOX_HEIGHT_SHELL) / 2;
			isDie = true;
		}
		count_start = GetTickCount64();
		vx = 0;
		break;
	case KOOPATROOPA_STATE_SHELL_MOVING:
		ay = KOOPATROOPA_GRAVITY;
		break;
	case KOOPATROOPA_STATE_SHELL_ALIVE:
		break;
	case KOOPATROOPA_STATE_ALIVE:
		count_start = -1;
		ay = KOOPATROOPA_GRAVITY;
		y -= (KOOPATROOPA_BBOX_HEIGHT - KOOPATROOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = nx * KOOPATROOPA_SPEED;
		break;
	case KOOPATROOPA_STATE_TURN:
		removeFalObj();
		count_start = GetTickCount64();
		vx = -vx;
		nx = -nx;
		break;
	case PARA_KOOPATROOPA_STATE_JUMP:
		break;
	case KOOPATROOPA_STATE_SHELL_PICK_UP:
		vy = 0;
		ay = 0;
		vx = 0;
		break;
	}
}
