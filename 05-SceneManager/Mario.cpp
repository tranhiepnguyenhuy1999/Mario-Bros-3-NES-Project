#include <algorithm>
#include "debug.h"

#include "Game.h"
#include "SampleKeyEventHandler.h"

#include "Mario.h"

#include "Goomba.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Portal.h"
#include "QuestionBrick.h"
#include "DownBrick.h"
#include "KoopaTroopa.h"
#include "ParaKoopaTroopa.h"
#include "Fire.h"
#include "ParaGoomba.h"
#include "Leaf.h"
#include "Tail.h"
#include "ShootingFlower.h"
#include "Button.h"

#include "AssetIDs.h"
#include "Collision.h"
#include "UserBoard.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (isFly)
	{
		if (GetTickCount64() - fly_start > MARIO_FLY_TIME)
		{
			isFly = false;
		}
		// check player is keep pressing S button
		else if (GetTickCount64() - fly_remain_start > MARIO_FLY_REMAIN_TIME)
		{
			ay = MARIO_GRAVITY;
			vx = 0;
		}
	}
	else if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CParaGoomba*>(e->obj))
		OnCollisionWithParaGoomba(e);
	else if (dynamic_cast<CParaKoopaTroopa*>(e->obj))
		OnCollisionWithParaKoopaTroopa(e);
	else if (dynamic_cast<CKoopaTroopa*>(e->obj))
		OnCollisionWithKoopaTroopa(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CDownBrick*>(e->obj))
		OnCollisionWithDownBrick(e);
	else if (dynamic_cast<CShootingFlower*>(e->obj))
		OnCollisionWithFlower(e);
	//else if (dynamic_cast<CFire*>(e->obj))
	//	OnCollisionWithFire(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CButton*>(e->obj))
		OnCollisionWithButton(e);
}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}
void CMario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* obj = dynamic_cast<CParaGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{

		if (obj->GetState() != PARAGOOMBA_STATE_DIE)
		{
			if (obj->getLevel() == PARAGOOMBA_LEVEL_FLY)
			{
				obj->setLevel(PARAGOOMBA_LEVEL_NORMAL);
			}
			else
			{
				obj->SetState(PARAGOOMBA_STATE_DIE);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	//else // hit by Goomba
	//{
	//	if (untouchable == 0)
	//	{
	//		if (obj->GetState() != PARAGOOMBA_STATE_DIE)
	//		{
	//			if (level > MARIO_LEVEL_SMALL)
	//			{
	//				level = MARIO_LEVEL_SMALL;
	//				StartUntouchable();
	//			}
	//			else
	//			{
	//				DebugOut(L">>> Mario DIE >>> \n");
	//				SetState(MARIO_STATE_DIE);
	//			}
	//		}
	//	}
	//}
}
void CMario::OnCollisionWithFlower(LPCOLLISIONEVENT e)
{
		if (untouchable == 0)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
}
void CMario::OnCollisionWithFire(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level = level-1;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e)
{
	CKoopaTroopa* obj = dynamic_cast<CKoopaTroopa*>(e->obj);
	// jump on top >> kill Goomba and deflect a bit 
	if (obj->GetState() == KOOPATROOPA_STATE_SHELL || obj->GetState() == KOOPATROOPA_STATE_ALIVE) {
		obj->getKicked(nx);
	}
	else if (e->ny < 0)
	{
		obj->getJumpedDown();
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	//else
	//{
	//	if (untouchable == 0)
	//	{
	//		if (obj->GetState() != KOOPATROOPA_STATE_SHELL)
	//		{
	//			if (level > MARIO_LEVEL_SMALL)
	//			{
	//				level = MARIO_LEVEL_SMALL;
	//				StartUntouchable();
	//			}
	//			else
	//			{
	//				SetState(MARIO_STATE_DIE);
	//			}
	//		}
	//	}
	//}
}
void CMario::OnCollisionWithParaKoopaTroopa(LPCOLLISIONEVENT e)
{
	CParaKoopaTroopa* obj = dynamic_cast<CParaKoopaTroopa*>(e->obj);
	// jump on top >> kill Goomba and deflect a bit 
	if (obj->GetState() == KOOPATROOPA_STATE_SHELL || obj->GetState() == KOOPATROOPA_STATE_ALIVE) {
	}
	else if (e->ny < 0)
	{
		// parakoopatroopa
		if (obj->GetState() == PARA_KOOPATROOPA_STATE_JUMP)
		{
			obj->SetState(KOOPATROOPA_STATE_MOVING);
		}
		else
		{
			if (obj->GetState() == KOOPATROOPA_STATE_MOVING)
			{
				obj->SetState(KOOPATROOPA_STATE_SHELL);
			}
		}
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		return;
	}
	//else 
	//{
	//	if (untouchable == 0)
	//	{
	//		if (obj->GetState() != KOOPATROOPA_STATE_SHELL)
	//		{
	//			if (level > MARIO_LEVEL_SMALL)
	//			{
	//				level = MARIO_LEVEL_SMALL;
	//				StartUntouchable();
	//			}
	//			else
	//			{
	//				DebugOut(L">>> Mario DIE >>> \n");
	//				SetState(MARIO_STATE_DIE);
	//			}
	//		}
	//	}
	//}
}
void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* obj = dynamic_cast<CQuestionBrick*>(e->obj);

	if (obj->GetState() != QUESTIONBRICK_STATE_UNACTIVE) return;

	if (e->ny > 0)
	{
			float qx, qy, qvx;
			obj->GetPosition(qx, qy);
			
			if (obj->getType() == 1)
			{
				CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_SMALLCOIN, qx, qy-16);
				CUserBoard::GetInstance()->updateProps(ID_PROP_COIN, +1);
				CUserBoard::GetInstance()->updateProps(ID_PROP_POINT, +100);
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
				if (level == MARIO_LEVEL_BIG)
				{
					CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_LEAF, qx, qy);
					CUserBoard::GetInstance()->updateProps(ID_PROP_POINT, +1000);
				}
				else
				{			
					CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_MUSHROOM, qx, qy, qvx);
					CUserBoard::GetInstance()->updateProps(ID_PROP_POINT, +1000);
				}
			}

			obj->SetState(QUESTIONBRICK_STATE_TOUCHED);
	}

}
void CMario::OnCollisionWithDownBrick(LPCOLLISIONEVENT e)
{
	CDownBrick* downBrick = dynamic_cast<CDownBrick*>(e->obj);
	if (e->ny < 0)
	{
		isOnPlatform = true;
		vy = 0;
	}
}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (level == MARIO_LEVEL_SMALL) {
	level = MARIO_LEVEL_BIG;
	}
	y = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	level = MARIO_LEVEL_RACOON;
	SetState(MARIO_STATE_RACOON_TRANSFORM);
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CUserBoard::GetInstance()->updateProps(ID_PROP_COIN, +1);
}
void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	CButton* obj = dynamic_cast<CButton*>(e->obj);
	if(obj->GetState() != BUTTON_STATE_ACTIVE) obj->SetState(BUTTON_STATE_ACTIVE);
}
void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (isFly) {
		aniId = ID_ANI_RACOON_FLY_RIGHT;
	}
	else
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_RACOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_RACOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_RACOON_IDLE_RIGHT;
				else aniId = ID_ANI_RACOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_RACOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_RACOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == MARIO_STATE_RACOON_TRANSFORM) aniId = ID_ANI_RACOON_TRANSFORM;
	else if (state == MARIO_STATE_ATTACK)
	{
	 if(nx>0)
		aniId = ID_ANI_RACOON_ATTACK_RIGHT;
	 else
		 aniId = ID_ANI_RACOON_ATTACK_LEFT;
	}
	else if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	if ((this->state == MARIO_STATE_RACOON_TRANSFORM) && (GetTickCount64() - count_start < 500)) return;
	if ((this->state == MARIO_STATE_ATTACK) && (GetTickCount64() - count_start < 500)) return;
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;

		if (!isFly && GetTickCount64() - next_pre_fly_mark_count_start > 250) {
			pre_fly_mark++;
			
			if (pre_fly_mark == 5) {
				SetState(MARIO_STATE_START_FLY);
				next_pre_fly_mark_count_start = -1;
			}
			else next_pre_fly_mark_count_start = GetTickCount64();
		}
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		else {
			if (level == 3) {
				vy = -0.15f;
			}
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	case MARIO_STATE_IDLE:
		if (isFly) break;
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_ATTACK:
		if (level != 3) return;
		count_start = GetTickCount64();
		createTailObject();
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_START_FLY:
		isFly = true;
		ay = 0;
		vy = 0;
		fly_start = GetTickCount64();
		break;
	case MARIO_STATE_FLY:
		fly_remain_start = GetTickCount64();
		vy = -MARIO_FLY_SPEED;
		break;
	case MARIO_STATE_RELEASE_FLY:
		break;
	case MARIO_STATE_RACOON_TRANSFORM:
		count_start = GetTickCount64();
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level!=MARIO_LEVEL_SMALL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}
void CMario::createTailObject() {

	if (nx < 0) {
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_TAIL, x - TAIL_BBOX_WIDTH / 2, y+ MARIO_BIG_BBOX_HEIGHT/2 - TAIL_BBOX_HEIGHT, -1);
	}
	else
	{
		CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_TAIL, x + TAIL_BBOX_WIDTH / 2, y + MARIO_BIG_BBOX_HEIGHT / 2 - TAIL_BBOX_HEIGHT,1);

	}
}
void CMario::onKeyUpOfWorldmapMario(int KeyCode) {
};
void CMario::onKeyDownOfWorldmapMario(int KeyCode) {};
void CMario::onKeyUpOfMainMario(int KeyCode) {
	
	switch (KeyCode)
	{
	case DIK_DOWN:
		//mario->GetPosition(x, y);
		//if (x >= 2256 && x <= 2288) {
		//	mario->SetPosition(2114, 544);
		//}
		SetState(MARIO_STATE_SIT);
		break;
	case DIK_UP:
		break;
	case DIK_A:
		SetState(MARIO_STATE_ATTACK);
		break;
	case DIK_S:
		if (isFly && level == 3) SetState(MARIO_STATE_FLY);
		else SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_0:
		SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
};
void CMario::onKeyDownOfMainMario(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_S:
		if (isFly && level == 3)
		{
			SetState(MARIO_STATE_RELEASE_FLY);
		}
		else
		{
			SetState(MARIO_STATE_RELEASE_JUMP);
		}
		break;
	case DIK_DOWN:
		SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
};
void CMario::keyStateOfMainMario() {
	LPGAME game = CGame::GetInstance();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else
			SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			SetState(MARIO_STATE_RUNNING_LEFT);
		else
			SetState(MARIO_STATE_WALKING_LEFT);
	}
	else SetState(MARIO_STATE_IDLE);
};
void CMario::handleKeyEvent(int flag, int KeyCode) {
	switch (this->type)
	{
	case MARIO_TYPE_MAIN:
	{
		switch (flag)
		{
		case KEYEVENT_KEY_UP:
			onKeyUpOfMainMario(KeyCode);
			break;
		case KEYEVENT_KEY_DOWN:
			onKeyUpOfMainMario(KeyCode);
			break;
		case KEYEVENT_KEY_STATE:
			keyStateOfMainMario();
			break;
		}
		break;
	}
	case MARIO_TYPE_WORLDMAP:
		break;
	}
}