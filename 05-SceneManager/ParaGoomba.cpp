#include "ParaGoomba.h"
#include "QuestionBrick.h"
#include "AssetIDs.h"

CParaGoomba::CParaGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	vy = PARAGOOMBA_JUMP_SPEED;
	ready_jump_start = -1;
	//this->ay = PARAGOOMBA_GRAVITY;
	count_start = -1;
	SetState(PARAGOOMBA_STATE_WALKING);
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARAGOOMBA_STATE_DIE || state == PARAGOOMBA_STATE_ALIVE)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - (PARAGOOMBA_BBOX_HEIGHT_DIE / 2);
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - (PARAGOOMBA_BBOX_HEIGHT / 2);
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParaGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		if (e->ny < 0)
		{
			//if (ready_jump_start == -1)
			//{			
			//	ready_jump_start = GetTickCount64();
			//	return;
			//}
			//if (GetTickCount64() - ready_jump_start > PARAGOOMBA_JUMP_TIMEOUT)
			//{
			SetState(PARAGOOMBA_STATE_JUMP);
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

void CParaGoomba::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
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
void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	//DebugOut(L"count %d", GetTickCount64() - count_start);
	if ((state == PARAGOOMBA_STATE_DIE) && (GetTickCount64() - count_start > PARAGOOMBA_DIE_TIMEOUT))
	{
		SetState(PARAGOOMBA_STATE_ALIVE);
		return;
	}
	if ((state == PARAGOOMBA_STATE_ALIVE) && (GetTickCount64() - count_start > PARAGOOMBA_ALIVE_TIMEOUT))
	{
		SetState(PARAGOOMBA_STATE_WALKING);
		count_start = -1;
		y = y + (PARAGOOMBA_BBOX_HEIGHT_DIE / 2) - PARAGOOMBA_BBOX_HEIGHT / 2;
		return;
	}
	if ((state == PARAGOOMBA_STATE_JUMP) && (GetTickCount64() - count_start > PARAGOOMBA_JUMP_TIMEOUT))
	{
		SetState(PARAGOOMBA_STATE_RELEASE_JUMP);
		count_start = -1;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaGoomba::Render()
{
	int aniId = ID_ANI_PARAGOOMBA_WALKING;
	if (state == PARAGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARAGOOMBA_DIE;
	}
	if (state == PARAGOOMBA_STATE_ALIVE)
	{
		aniId = ID_ANI_PARAGOOMBA_ALIVE;
	}
	if (state == PARAGOOMBA_STATE_KICKING)
	{
		aniId = ID_ANI_PARAGOOMBA_KICKING;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAGOOMBA_STATE_DIE:
		count_start = GetTickCount64();
		y += (PARAGOOMBA_BBOX_HEIGHT - PARAGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARAGOOMBA_STATE_ALIVE:
		count_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARAGOOMBA_STATE_JUMP:
		count_start = GetTickCount64();
		vy = -PARAGOOMBA_JUMP_SPEED;
		break;
	case PARAGOOMBA_STATE_RELEASE_JUMP:
		vy = PARAGOOMBA_JUMP_SPEED;
		break;
	case PARAGOOMBA_STATE_WALKING:
		vx = -PARAGOOMBA_WALKING_SPEED;
		break;
	case PARAGOOMBA_STATE_KICKING:
		vx = PARAGOOMBA_KICKING_SPEED;
		break;
	}
}
