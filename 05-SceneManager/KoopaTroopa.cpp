#include "KoopaTroopa.h"
#include "QuestionBrick.h"
#include "AssetIDs.h"

CKoopaTroopa::CKoopaTroopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	vy = KOOPATROOPA_JUMP_SPEED;
	ready_jump_start = -1;
	//this->ay = KOOPATROOPA_GRAVITY;
	count_start = -1;
	SetState(KOOPATROOPA_STATE_WALKING);
}

void CKoopaTroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPATROOPA_STATE_DIE || state== KOOPATROOPA_STATE_ALIVE)
	{
		left = x - KOOPATROOPA_BBOX_WIDTH / 2;
		top = y - (KOOPATROOPA_BBOX_HEIGHT_DIE / 2);
		right = left + KOOPATROOPA_BBOX_WIDTH;
		bottom = top + KOOPATROOPA_BBOX_HEIGHT_DIE;
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
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopaTroopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		if (e->ny < 0)
		{
			//if (ready_jump_start == -1)
			//{			
			//	ready_jump_start = GetTickCount64();
			//	return;
			//}
			//if (GetTickCount64() - ready_jump_start > KOOPATROOPA_JUMP_TIMEOUT)
			//{
				SetState(KOOPATROOPA_STATE_JUMP);
	/*			ready_jump_start = -1;
			}*/
		}
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CQuestionBrick*>(e->obj))OnCollisionWithQuestionBrick(e);
}

void CKoopaTroopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
		if (questionBrick->GetState() == QUESTIONBRICK_STATE_UNTOUCHED)
		{
			float qx, qy, qvx;
			questionBrick->GetPosition(qx, qy);

			if (questionBrick->getType() == 1)
			{
				CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_SMALLCOIN, qx, qy - 16);
			}
			else
			{
				// check direction
				if (this->x <= qx + 8) {
					qvx = -1;
				}
				else
				{
					qvx = 1;
				}
				CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_MUSHROOM, qx, qy, qvx);
			}

			questionBrick->SetState(QUESTIONBRICK_STATE_TOUCHED_1);
		}

}
void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	//DebugOut(L"count %d", GetTickCount64() - count_start);
	if ((state == KOOPATROOPA_STATE_DIE) && (GetTickCount64() - count_start > KOOPATROOPA_DIE_TIMEOUT))
	{
		SetState(KOOPATROOPA_STATE_ALIVE);
		return;
	}
	if ((state == KOOPATROOPA_STATE_ALIVE) && (GetTickCount64() - count_start > KOOPATROOPA_ALIVE_TIMEOUT))
	{
		SetState(KOOPATROOPA_STATE_WALKING);
		count_start = -1;
		y = y + (KOOPATROOPA_BBOX_HEIGHT_DIE/2) - KOOPATROOPA_BBOX_HEIGHT/2 ;
		return;
	}
	if ((state == KOOPATROOPA_STATE_JUMP) && (GetTickCount64() - count_start > KOOPATROOPA_JUMP_TIMEOUT))
	{
		SetState(KOOPATROOPA_STATE_RELEASE_JUMP);
		count_start = -1;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopaTroopa::Render()
{
	int aniId = ID_ANI_KOOPATROOPA_WALKING;
	if (state == KOOPATROOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPATROOPA_DIE;
	}
	if (state == KOOPATROOPA_STATE_ALIVE)
	{
		aniId = ID_ANI_KOOPATROOPA_ALIVE;
	}
	if (state == KOOPATROOPA_STATE_KICKING)
	{
		aniId = ID_ANI_KOOPATROOPA_KICKING;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopaTroopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPATROOPA_STATE_DIE:
		count_start = GetTickCount64();
		y += (KOOPATROOPA_BBOX_HEIGHT - KOOPATROOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPATROOPA_STATE_ALIVE:
		count_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPATROOPA_STATE_JUMP:
		count_start = GetTickCount64();
		vy = -KOOPATROOPA_JUMP_SPEED;
		break;
	case KOOPATROOPA_STATE_RELEASE_JUMP:
		vy = KOOPATROOPA_JUMP_SPEED;
		break;
	case KOOPATROOPA_STATE_WALKING:
		vx = -KOOPATROOPA_WALKING_SPEED;
		break;
	case KOOPATROOPA_STATE_KICKING:
		vx = KOOPATROOPA_KICKING_SPEED;
		break;
	}
}
