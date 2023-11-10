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
#include "ChangePositionBlock.h"
#include "TransportPile.h"
#include "Card.h"

#include "AssetIDs.h"
#include "Collision.h"
#include "UserBoard.h"
#include "Layer.h"
#include "Camera.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (type == MARIO_TYPE_WORLDMAP && abs(vy) > abs(maxVy)) vy = maxVy;

	// reset untouchable timer if untouchable time has passed

	if (pickup_shell) {
		DebugOut(L"Start pickup shell !!! \n");

		if (!pickup_shell->IsDie())
			pickup_shell = NULL;
		else
		{
			if (prev_nx != nx) pickup_shell->SetPosition(x + nx * MARIO_BIG_BBOX_WIDTH / 2 + nx * KOOPATROOPA_BBOX_WIDTH / 3, y + MARIO_BIG_BBOX_HEIGHT / 8);
			pickup_shell->getPickUp(vx);
		}
	}
	
	if (low_fly_remain_start != -1)
	{
		if (GetTickCount64() - low_fly_remain_start > 250) {
			ay = MARIO_GRAVITY;
			low_fly_remain_start = -1;
		}
	}

	if (next_ready_to_fly_mark_count_start != -1)
	{
		DebugOut(L"Minus ready fly mark !!! \n");

		if (!isReadyToFly && GetTickCount64() - next_ready_to_fly_mark_count_start > 350)
		{
			ready_to_fly_mark--;
			if (ready_to_fly_mark < -1)
			{
				next_ready_to_fly_mark_count_start = -1;
			}
			else next_ready_to_fly_mark_count_start=GetTickCount64();
			
			UserInfo::GetInstance()->updateProps(ID_PROPS_FLY_MARK, ready_to_fly_mark);

		}
	}
	else if (isFlying)
	{
		DebugOut(L"Flying time !!! \n");

		if (GetTickCount64() - fly_start > MARIO_FLY_TIME)
		{
			SetState(MARIO_STATE_END_FLY);
		}
		// check player is keep pressing S button
		else if (GetTickCount64() - fly_remain_start > MARIO_FLY_REMAIN_TIME)
		{
			SetState(MARIO_STATE_RELEASE_FLY);
		}
	}
	else if (isInPile && GetTickCount64()- count_start > 100) {
		DebugOut(L"Start in pile !!! \n");
		isInPile = false;
	}
	else if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	this->prev_nx = nx;
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
		
		if (dynamic_cast<CTransportPile*>(e->obj)) isOnTransportPile = true; else isOnTransportPile = false;

		if (e->ny < 0)
		{
			isOnPlatform = true;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
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
	else if (dynamic_cast<CChangePositionBlock*>(e->obj))
		OnCollisionWithChangePositionBlock(e);
	else if (dynamic_cast<CCard*>(e->obj))
		OnCollisionWithCard(e);
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
			goomba->AddPointToUserBoard();

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
			
			obj->AddPointToUserBoard();

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
void CMario::OnCollisionWithChangePositionBlock(LPCOLLISIONEVENT e)
{
	CChangePositionBlock* obj = dynamic_cast<CChangePositionBlock*>(e->obj);
	obj->handlePlayerTouched();
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
	if (obj->GetState() == KOOPATROOPA_STATE_SHELL || obj->GetState() == KOOPATROOPA_STATE_SHELL_ALIVE) {
		if (e->nx != 0 && isRuning){
			obj->SetState(KOOPATROOPA_STATE_SHELL_PICK_UP);
			obj->SetPosition(x + nx*MARIO_BIG_BBOX_WIDTH/2 + nx*KOOPATROOPA_BBOX_WIDTH/3, y + MARIO_BIG_BBOX_HEIGHT/8);
			pickup_shell = obj;
		}
		else
		{
			SetState(MARIO_STATE_KICK);
			obj->getKicked(nx);
		}
	}
	else if (e->ny < 0)
	{
		obj->getJumpedDown();
		obj->AddPointToUserBoard();

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
		obj->AddPointToUserBoard();

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
			float objx, objy;
			obj->GetPosition(objx, objy);
			
			if (obj->getType() == 1)
			{
				CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_SMALLCOIN, objx, objy - 16);
				UserInfo::GetInstance()->updateProps(ID_PROPS_COIN, +1);
			}
			else
			{
				if (level == MARIO_LEVEL_BIG)
				{
					CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_LEAF, objx, objy);
				}
				else
				{			
					CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_MUSHROOM, objx, objy, (float)nx);
				}
				obj->AddPointToUserBoard();
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
	if (level == MARIO_LEVEL_SMALL) level = MARIO_LEVEL_BIG;
	
	y = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
	
	e->obj->AddPointToUserBoard();
	e->obj->Delete();
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	level = MARIO_LEVEL_RACOON;
	SetState(MARIO_STATE_RACOON_TRANSFORM);
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->AddPointToUserBoard();
	e->obj->Delete();
}
void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	CButton* obj = dynamic_cast<CButton*>(e->obj);
	if(obj->GetState() != BUTTON_STATE_ACTIVE) obj->SetState(BUTTON_STATE_ACTIVE);
}
void CMario::OnCollisionWithCard(LPCOLLISIONEVENT e)
{
	CCard* obj = dynamic_cast<CCard*>(e->obj);
	if (obj->GetState() != CARD_STATE_TOUCHED)
	{
		obj->SetState(CARD_STATE_TOUCHED);
		obj->handlePlayerTouched();
	}
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
		else if (isKicking) {
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
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
		else if (isKicking) {
			if (nx > 0) aniId = ID_ANI_MARIO_KICK_RIGHT;
			else aniId = ID_ANI_MARIO_KICK_LEFT;
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
	if (isFlying && !isOnPlatform) {
		if (nx >= 0)
			aniId = ID_ANI_RACOON_FLY_RIGHT;
		else
			aniId = ID_ANI_RACOON_FLY_LEFT;
	}
	else if (isReadyToFly && isRuning)
	{
		if (nx >= 0)
			aniId = ID_ANI_RACOON_READY_FLY_RIGHT;
		else
			aniId = ID_ANI_RACOON_READY_FLY_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
			{
				if (vy > 0)
				{
					aniId = ID_ANI_RACOON_LOW_FLY_RIGHT;
				}
				else aniId = ID_ANI_RACOON_JUMP_RUN_RIGHT;
			}
			else
				aniId = ID_ANI_RACOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
			{
				if (vy > 0)
				{
					if(low_fly_remain_start != -1) aniId = ID_ANI_RACOON_LOW_FLY_RIGHT;
					else aniId = ID_ANI_RACOON_JUMP_WALK_DOWN_RIGHT;
				}
				else aniId = ID_ANI_RACOON_JUMP_WALK_RIGHT;
			}
			else
			{
				if (vy > 0)
				{
					if (low_fly_remain_start != -1) aniId = ID_ANI_RACOON_LOW_FLY_LEFT;
					else aniId = ID_ANI_RACOON_JUMP_WALK_DOWN_LEFT;
				}
				else aniId = ID_ANI_RACOON_JUMP_WALK_LEFT;
			}
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
		else if (isKicking) {
			if (nx > 0) aniId = ID_ANI_RACOON_KICK_RIGHT;
			else aniId = ID_ANI_RACOON_KICK_LEFT;
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

	if (type == MARIO_TYPE_WORLDMAP) aniId = ID_ANI_MARIO_WORLDMAP;
	else if (state == MARIO_STATE_RACOON_TRANSFORM) aniId = ID_ANI_RACOON_TRANSFORM;
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

	RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	if (this->state == MARIO_STATE_RACOON_TRANSFORM && (GetTickCount64() - count_start < 500)) return;
	else if (this->state == MARIO_STATE_ATTACK && (GetTickCount64() - count_start < 500)) return;
	// DIE is the end state, cannot be changed! 
	else if (this->state == MARIO_STATE_DIE) return; 


	if (isKicking && (GetTickCount64() - count_start > 150))
	{
		isKicking = false;
	}

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		isRuning = true;
		if (!isReadyToFly && GetTickCount64() - next_ready_to_fly_mark_count_start > 250) { 
			
			ready_to_fly_mark++;

			if (ready_to_fly_mark > 6) {
				SetState(MARIO_STATE_START_FLY);
				next_ready_to_fly_mark_count_start = -1;
			}
			else next_ready_to_fly_mark_count_start = GetTickCount64();

			UserInfo::GetInstance()->updateProps(ID_PROPS_FLY_MARK, ready_to_fly_mark);
		}
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		isRuning = true;
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
	case MARIO_STATE_WALKING_UP:
		if (isSitting) break;
		maxVy = -MARIO_WALKING_SPEED;
		ay = -MARIO_ACCEL_WALK_X;
		break;
	case MARIO_STATE_WALKING_DOWN:
		if (isSitting) break;
		maxVy = MARIO_WALKING_SPEED;
		ay = MARIO_ACCEL_WALK_X;
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
		else if(level == MARIO_LEVEL_RACOON)
		{
			if (GetTickCount64() - low_fly_remain_start > 250) break;
			if (vy > 0)
			{
				ay = 0.0f;
				vy = 0.05f;
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
		if (isFlying && !isOnPlatform) break;
		if (type == MARIO_TYPE_WORLDMAP) {
			ay = 0.0f;
			vy = 0.0f;
		}
		ax = 0.0f;
		vx = 0.0f;
		isRuning = false;
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
		isReadyToFly = true;
		vy = 0;
		fly_start = GetTickCount64();
		break;
	case MARIO_STATE_FLY:
		isFlying = true;
		ay = 0;
		vy = -MARIO_FLY_SPEED;
		fly_remain_start = GetTickCount64();
		break;
	case MARIO_STATE_END_FLY:
		isFlying = false;
		isReadyToFly = false;
		ready_to_fly_mark = -1;
		UserInfo::GetInstance()->updateProps(ID_PROPS_FLY_MARK, ready_to_fly_mark);
		ay = MARIO_GRAVITY;
		break;
	case MARIO_STATE_RELEASE_FLY:
		ay = MARIO_GRAVITY;
		break;
	case MARIO_STATE_KICK:
		isKicking = true;
		count_start = GetTickCount64();
		break;
	case MARIO_STATE_RACOON_TRANSFORM:
		count_start = GetTickCount64();
		break;
	case MARIO_STATE_GO_DOWN_PILE:
		ay = 0;
		vy = MARIO_IN_PILE_SPEED;
		vx = 0;
		ax = 0;
		isInPile = true;
		count_start = GetTickCount64();
		break;
	case MARIO_STATE_GO_UP_PILE:
		ay = 0;
		vy = -MARIO_IN_PILE_SPEED;
		vx = 0;
		ax = 0;
		isInPile = true;
		count_start = GetTickCount64();
		break;
	case MARIO_STATE_OUT_PILE:
		vy = 0;
		ay = MARIO_GRAVITY;
		isInPile = false;
		count_start = -1;
		break;
	}
	CGameObject::SetState(state);
}
void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level == MARIO_LEVEL_RACOON)
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
			left = x - RACOON_SPRITE_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + RACOON_SPRITE_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_BIG)
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
	switch (KeyCode)
	{
	case DIK_S:
			CGame::GetInstance()->InitiateSwitchScene(5);
		break;
	}
};
void CMario::onKeyDownOfWorldmapMario(int KeyCode) {};
void CMario::onKeyUpOfMainMario(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (isOnTransportPile) {
			SetState(MARIO_STATE_GO_DOWN_PILE);
		}
		else SetState(MARIO_STATE_SIT);
		break;
	case DIK_UP:
		break;
	case DIK_A:
		SetState(MARIO_STATE_ATTACK);
		break;
	case DIK_S:
		if (isReadyToFly && level == MARIO_LEVEL_RACOON) SetState(MARIO_STATE_FLY);
		else {
			SetState(MARIO_STATE_JUMP);
			low_fly_remain_start = GetTickCount64();
		}
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
		if (isReadyToFly) break;
		SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_A:
		isRuning = false;
		if (pickup_shell) {
			pickup_shell->getKicked(nx);
			pickup_shell = NULL;
			SetState(MARIO_STATE_KICK);
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
void CMario::keyStateOfWorldmapMario() {
	LPGAME game = CGame::GetInstance();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		SetState(MARIO_STATE_WALKING_UP);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		SetState(MARIO_STATE_WALKING_DOWN);
	}
	else SetState(MARIO_STATE_IDLE);
};
void CMario::handleKeyEvent(int flag, int KeyCode) {
	switch ((int)this->type)
	{
	case MARIO_TYPE_MAIN:
	{
		//if (isInPile) break;
		switch (flag)
		{
		case KEYEVENT_KEY_UP:
			onKeyUpOfMainMario(KeyCode);
			break;
		case KEYEVENT_KEY_DOWN:
			onKeyDownOfMainMario(KeyCode);
			break;
		case KEYEVENT_KEY_STATE:
			keyStateOfMainMario();
			break;
		}
		break;
	}
	case MARIO_TYPE_WORLDMAP:
	{
		//if (isInPile) break;
		switch (flag)
		{
		case KEYEVENT_KEY_UP:
			onKeyUpOfWorldmapMario(KeyCode);
			break;
		case KEYEVENT_KEY_DOWN:
			onKeyDownOfWorldmapMario(KeyCode);
			break;
		case KEYEVENT_KEY_STATE:
			keyStateOfWorldmapMario();
			break;
		}
		break;
	}
	}
}