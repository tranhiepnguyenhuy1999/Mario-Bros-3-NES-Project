#include "ShootingFlower.h"
#include "AssetIDs.h"
#include "Pile.h"
#include "Camera.h"
#include "debug.h"
CShootingFlower::CShootingFlower(float x, float y, float type) :CGameObject(x, y)
{
	ay = 0;
	top = y - SHOOTING_FLOWER_BBOX_HEIGHT;
	bot = y;
	loop_start = -1;
	is_after_shooting = false;
	isWorking = true;
	this->type = type;
	SetState(SHOOTING_FLOWER_STATE_STATIC);
}

void CShootingFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SHOOTING_FLOWER_BBOX_WIDTH / 2;
	top = y - (SHOOTING_FLOWER_BBOX_HEIGHT / 2);
	right = left + SHOOTING_FLOWER_BBOX_WIDTH;
	bottom = top + SHOOTING_FLOWER_BBOX_HEIGHT;
}

void CShootingFlower::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CShootingFlower::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CShootingFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float px, py;
	Camera::GetInstance()->getPlayerPosition(px, py);

	vy += ay * dt;

	x += vx * dt;
	y += vy * dt;

	if (!isWorking) {
		if (abs(px - x) > SHOOTING_FLOWER_UNWORKING_RANGE) isWorking = true;
		return;
	}

	if (y < top)
	{
		y = top;
		SetState(SHOOTING_FLOWER_STATE_STATIC);
	}
	else if (y > bot)
	{
		y = bot;
		SetState(SHOOTING_FLOWER_STATE_STATIC);
	}

	if (state == SHOOTING_FLOWER_STATE_STATIC)
	{
		if (y == top)
		{
			if (is_after_shooting && (GetTickCount64() - loop_start > SHOOTING_FLOWER_AFSHOOT_TIMEOUT)) {
				is_after_shooting = false;
				SetState(SHOOTING_FLOWER_STATE_MOVE);
			}
			else if (!is_after_shooting && GetTickCount64() - loop_start > SHOOTING_FLOWER_PRESHOOT_TIMEOUT)
			{
				is_after_shooting = true;
				loop_start = GetTickCount64();
				shooting();
			}
		}
		else if (y == bot && abs(px - x) < SHOOTING_FLOWER_UNWORKING_RANGE) isWorking = false;

		else if (y == bot && (GetTickCount64() - loop_start > SHOOTING_FLOWER_LOOP_TIMEOUT))
		{
			SetState(SHOOTING_FLOWER_STATE_MOVE);
		}
	}

	CGameObject::Update(dt, coObjects);
}
int CShootingFlower::getMovingFlowerAniId(int flag) {
	switch (flag)
	{
	case 1:
		return ID_ANI_SHOOTING_FLOWER_UP_LEFT_MOVING;
	case 2:
		return ID_ANI_SHOOTING_FLOWER_DOWN_LEFT_MOVING;
	case 3:
		return ID_ANI_SHOOTING_FLOWER_UP_RIGHT_MOVING;
	case 4:
		return ID_ANI_SHOOTING_FLOWER_DOWN_RIGHT_MOVING;
	}

};
int CShootingFlower::getStaticFlowerAniId(int flag) {
	switch (flag)
	{
	case 1:
		return ID_ANI_SHOOTING_FLOWER_UP_LEFT_IDLE;
	case 2:
		return ID_ANI_SHOOTING_FLOWER_DOWN_LEFT_IDLE;
	case 3:
		return ID_ANI_SHOOTING_FLOWER_UP_RIGHT_IDLE;
	case 4:
		return ID_ANI_SHOOTING_FLOWER_DOWN_RIGHT_IDLE;
	}
};
int CShootingFlower::getMovingFlowerType2AniId(int flag) {
	switch (flag)
	{
	case 1:
		return ID_ANI_SHOOTING_FLOWER2_UP_LEFT_MOVING;
	case 2:
		return ID_ANI_SHOOTING_FLOWER2_DOWN_LEFT_MOVING;
	case 3:
		return ID_ANI_SHOOTING_FLOWER2_UP_RIGHT_MOVING;
	case 4:
		return ID_ANI_SHOOTING_FLOWER2_DOWN_RIGHT_MOVING;
	}

};
int CShootingFlower::getStaticFlowerType2AniId(int flag) {
	switch (flag)
	{
	case 1:
		return ID_ANI_SHOOTING_FLOWER2_UP_LEFT_IDLE;
	case 2:
		return ID_ANI_SHOOTING_FLOWER2_DOWN_LEFT_IDLE;
	case 3:
		return ID_ANI_SHOOTING_FLOWER2_UP_RIGHT_IDLE;
	case 4:
		return ID_ANI_SHOOTING_FLOWER2_DOWN_RIGHT_IDLE;
	}
};
int CShootingFlower::getFlowerPosition() {
	float px, py;
	Camera::GetInstance()->getPlayerPosition(px, py);

	if (px < x) {
		if (py < y) return 1; //top-left
		else return 2; //bot-left
	}
	else
	{
		if (py < y) return 3; //top-right
		else return 4; // bot-right
	}
}
void CShootingFlower::Render()
{
	int flag = getFlowerPosition();
	int aniId;

	if (this->state == SHOOTING_FLOWER_STATE_STATIC) {
		switch ((int)this->type)
		{
		case SHOOTING_FLOWER_TYPE_GREEN:
			aniId = getStaticFlowerAniId(flag);
			break;
		case SHOOTING_FLOWER_TYPE_RED:
			aniId = getStaticFlowerType2AniId(flag);
			break;
		}
	}
	else {
		switch ((int)this->type)
		{
		case SHOOTING_FLOWER_TYPE_GREEN:
			aniId = getMovingFlowerAniId(flag);
			break;
		case SHOOTING_FLOWER_TYPE_RED:
			aniId = getMovingFlowerType2AniId(flag);
			break;
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
void CShootingFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SHOOTING_FLOWER_STATE_STATIC:
		loop_start = GetTickCount64();
		ay = 0;
		vy = 0;
		break;
	case SHOOTING_FLOWER_STATE_MOVE:
		if (y == top) ay = SHOOTING_FLOWER_Y_AXIS;
		else if (y == bot) ay = -SHOOTING_FLOWER_Y_AXIS;
		break;
	}
}
int CShootingFlower::getPlayerPosition() {
	float px, py;
	Camera::GetInstance()->getPlayerPosition(px, py);

	// check position base on y
	if (px < x) {
		if (py < y) return 1; //left-top
		else return 2; //left-bottom
	}
	else
	{
		if (py < y) return 3; //right-top
		else return 4; //right-bottom
	}
}
void CShootingFlower::shooting()
{
	float nx = 0, ny = 0;
	float px, py;

	int flag = getPlayerPosition();
	Camera::GetInstance()->getPlayerPosition(px, py);

	switch (flag)
	{
	case 1:
		nx = -1; ny = -1;
		break;
	case 2:
		nx = -1; ny = 1;
		break;
	case 3:
		nx = 1; ny = -1;
		break;
	case 4:
		nx = 1; ny = 1;
		break;
	}

	float percentX = translateToPercent(x, true);
	float percentY = translateToPercent(y, false);
	//DebugOut(L">>> x: %f >>> \n", percentX);
	//DebugOut(L">>> y: %f >>> \n", percentY);
	float percent = percentX / percentY;
	float altShootingXSpeed = 1;
	float altShootingYSpeed = 1;
	//DebugOut(L">>> percent: %f >>> \n", percent);
	if (percent >= 4.0f)
	{
		altShootingYSpeed = 0.25f;
	}
	if (percent >= 2.0f)
	{
		altShootingYSpeed = 0.5f;
	}
	else if (percent < 1.0f)
	{
		altShootingXSpeed = 0.5f;
	}
	else if (percent < 0.5f)
	{
		altShootingXSpeed = 0.25f;
	}

	CGame::GetInstance()->GetCurrentScene()->createNewObject(OBJECT_TYPE_FIRE, x, y, nx * altShootingXSpeed, altShootingYSpeed * ny);
}
float CShootingFlower::translateToPercent(float data, boolean isXAxis) {
	float px, py;
	float result = 0;
	Camera::GetInstance()->getPlayerPosition(px, py);

	if (isXAxis)
	{
		result = abs(px - data) / SHOOTING_FLOWER_SHOOTING_RANGE;
	}
	else
	{
		result = abs(py - data) / SHOOTING_FLOWER_SHOOTING_RANGE;
	}


	if (result >= 1) return 10.0f;
	else if (result >= 0.9f) return 9.0f;
	else if (result >= 0.8f) return 8.0f;
	else if (result >= 0.7f) return 7.0f;
	else if (result >= 0.6f) return 6.0f;
	else if (result >= 0.5f) return 5.0f;
	else if (result >= 0.4f) return 4.0f;
	else if (result >= 0.3f) return 3.0f;
	else if (result >= 0.2f) return 2.0f;
	else return 1.0f;
}