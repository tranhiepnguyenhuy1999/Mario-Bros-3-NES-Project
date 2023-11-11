#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#include "KoopaTroopa.h"

#define MARIO_WALKING_SPEED		0.075f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0001f

#define MARIO_JUMP_SPEED_Y		0.335f
#define MARIO_JUMP_RUN_SPEED_Y	0.3f

#define MARIO_JUMP_DEFLECT_SPEED  0.2f

#define MARIO_GRAVITY	0.00075f
//#define MARIO_GRAVITY	0.0

#define MARIO_FLY_SPEED  0.075f
#define MARIO_IN_PILE_SPEED  0.025f



#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_ATTACK			700

#define MARIO_STATE_RACOON_TRANSFORM	800

#define MARIO_STATE_START_FLY	900
#define MARIO_STATE_FLY	1000
#define MARIO_STATE_RELEASE_FLY 1100
#define MARIO_STATE_END_FLY	1200

#define MARIO_STATE_KICK	1300

#define MARIO_STATE_GO_DOWN_PILE 1400
#define MARIO_STATE_GO_UP_PILE 1500
#define MARIO_STATE_OUT_PILE 1600

#define MARIO_STATE_WALKING_UP	1700
#define MARIO_STATE_WALKING_DOWN	1800

#define MARIO_STATE_UNCONTROL 1900

#pragma region ANIMATION_ID
// RACOON
#define	ID_ANI_RACOON_TRANSFORM 1700

#define ID_ANI_RACOON_IDLE_RIGHT 1700
#define ID_ANI_RACOON_IDLE_LEFT 1701

#define ID_ANI_RACOON_WALKING_RIGHT 1702
#define ID_ANI_RACOON_WALKING_LEFT 1703

#define ID_ANI_RACOON_RUNNING_RIGHT 1704
#define ID_ANI_RACOON_RUNNING_LEFT 1705

#define ID_ANI_RACOON_BRACE_RIGHT 1706
#define ID_ANI_RACOON_BRACE_LEFT 1707

#define ID_ANI_RACOON_JUMP_WALK_RIGHT 1708
#define ID_ANI_RACOON_JUMP_WALK_LEFT 1709

#define ID_ANI_RACOON_JUMP_RUN_RIGHT 1710
#define ID_ANI_RACOON_JUMP_RUN_LEFT 1711

#define ID_ANI_RACOON_ATTACK_RIGHT 1712
#define ID_ANI_RACOON_ATTACK_LEFT 1713

#define ID_ANI_RACOON_FLY_RIGHT 1714
#define ID_ANI_RACOON_FLY_LEFT 1715

#define ID_ANI_RACOON_KICK_RIGHT 1716
#define ID_ANI_RACOON_KICK_LEFT 1717

#define ID_ANI_RACOON_LOW_FLY_RIGHT 1718
#define ID_ANI_RACOON_LOW_FLY_LEFT 1719

#define ID_ANI_RACOON_JUMP_WALK_DOWN_RIGHT 1720
#define ID_ANI_RACOON_JUMP_WALK_DOWN_LEFT 1721

#define ID_ANI_RACOON_READY_FLY_RIGHT 1722
#define ID_ANI_RACOON_READY_FLY_LEFT 1723

#define ID_ANI_RACOON_IN_PILE 1724

#define ID_ANI_RACOON_SIT_RIGHT 1725
#define ID_ANI_RACOON_SIT_LEFT 1726

//BIG
#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501
	
#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_KICK_RIGHT 997
#define ID_ANI_MARIO_KICK_LEFT 998

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1602
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1603


// WORLDMAP
#define ID_ANI_MARIO_WORLDMAP 1650

#pragma endregion

#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON	3

#define	MARIO_TYPE_MAIN	0
#define	MARIO_TYPE_WORLDMAP		1

#define RACOON_SPRITE_WIDTH  22
#define RACOON_SPRITE_HEIGHT 28

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 28
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 18

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  12
#define MARIO_SMALL_BBOX_HEIGHT 16


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_FLY_TIME 10000
#define MARIO_FLY_REMAIN_TIME 250


class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx, maxVy;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	float type;
	int ready_to_fly_mark;
	int prev_nx;
	
	BOOLEAN isOnPlatform;
	BOOLEAN isOnTransportPile;
	BOOLEAN isReadyToFly;
	BOOLEAN isFlying;
	BOOLEAN	isRuning;
	BOOLEAN	isKicking;
	BOOLEAN isInPile;
	BOOLEAN isCanGoUpPile;
	BOOLEAN isUnControl;


	ULONGLONG untouchable_start;
	ULONGLONG count_start;
	ULONGLONG next_ready_to_fly_mark_count_start;
	ULONGLONG fly_start;
	ULONGLONG fly_remain_start;
	ULONGLONG low_fly_remain_start;

	CKoopaTroopa* pickup_shell;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithFire(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithDownBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithParaKoopaTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithButton(LPCOLLISIONEVENT e);
	void OnCollisionWithChangePositionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithCard(LPCOLLISIONEVENT e);
	void OnCollisionWithBreakBrick(LPCOLLISIONEVENT e);


	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

	void onKeyUpOfWorldmapMario(int KeyCode);
	void onKeyDownOfWorldmapMario(int KeyCode);
	void keyStateOfWorldmapMario();

	void onKeyUpOfMainMario(int KeyCode);
	void onKeyDownOfMainMario(int KeyCode);
	void keyStateOfMainMario();
public:
	CMario(float x, float y, float p_type) : CGameObject(x, y)
	{
		isSitting = false;
		isOnPlatform = false;
		isOnTransportPile = false;
		isReadyToFly = false;
		isFlying = false;
		isRuning = false;
		isKicking = false;
		isInPile = false;
		isCanGoUpPile = false;
		isUnControl = false;

		maxVx = 0.0f;
		maxVy = 0.0f;
		ax = 0.0f;
		ready_to_fly_mark = -1;
		level = MARIO_LEVEL_RACOON;
		type = p_type;
		if (p_type == MARIO_TYPE_MAIN) ay = MARIO_GRAVITY; else ay = 0;
		untouchable = 0;
		prev_nx = 0;
		
		untouchable_start = -1;
		count_start = -1;
		fly_start = -1;
		next_ready_to_fly_mark_count_start = -1;
		fly_remain_start = -1;
		low_fly_remain_start = -1;

		pickup_shell = NULL;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void getLevel(int& level) { level = this->level; }
	int IsCollidable()
	{
		switch (state)
		{
			case MARIO_STATE_DIE:
			case MARIO_STATE_GO_DOWN_PILE:
			case MARIO_STATE_GO_UP_PILE:
				return false;
			default:
				return true;
		}
	}
	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void createTailObject();
	void handleKeyEvent(int flag, int KeyCode);

};