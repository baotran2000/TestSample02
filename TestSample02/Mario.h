#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "Tail.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_RUNNING_MAX_SPEED 0.3f
#define MARIO_DECELERATE_SPEED 0.00012f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.0015f
#define MARIO_JUMP_SPEED_MAX 0.3f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_RACOON_FALL_SLOW_SPEED 0.03f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_KICK 402

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define	MARIO_RACOON_ATTACK	800
#define	MARIO_RACOON_ATTACK_RELEASE	801

#define MARIO_RACOON_STATE_FALL_SLOW 802
#define MARIO_RACOON_STATE_FLAPPING 803

#pragma region ANIMATION_ID

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

#define ID_ANI_MARIO_HOLD_IDLE_RIGHT 10019
#define ID_ANI_MARIO_HOLD_IDLE_LEFT 10020
#define ID_ANI_MARIO_HOLD_WALK_RIGHT 10021
#define ID_ANI_MARIO_HOLD_WALK_LEFT 10022

#define ID_ANI_MARIO_HOLD_JUMP_RIGHT 10025
#define ID_ANI_MARIO_HOLD_JUMP_LEFT 10026

//RACOON MARIO
#define ID_ANI_RACOON_MARIO_IDLE_RIGHT 3400
#define ID_ANI_RACOON_MARIO_IDLE_LEFT 3401

#define ID_ANI_RACOON_MARIO_WALKING_RIGHT 3500
#define ID_ANI_RACOON_MARIO_WALKING_LEFT 3501

#define ID_ANI_RACOON_MARIO_RUNNING_RIGHT 3600
#define ID_ANI_RACOON_MARIO_RUNNING_LEFT 3601

#define ID_ANI_RACOON_MARIO_JUMP_WALK_RIGHT 3700
#define ID_ANI_RACOON_MARIO_JUMP_WALK_LEFT 3701

#define ID_ANI_RACOON_MARIO_JUMP_RUN_RIGHT 3800
#define ID_ANI_RACOON_MARIO_JUMP_RUN_LEFT 3801

#define ID_ANI_RACOON_MARIO_SIT_RIGHT 3900
#define ID_ANI_RACOON_MARIO_SIT_LEFT 3901

#define ID_ANI_RACOON_MARIO_BRACE_RIGHT 3100
#define ID_ANI_RACOON_MARIO_BRACE_LEFT 3101

#define ID_ANI_RACOON_MARIO_ATTACK_FROM_LEFT 3200
#define ID_ANI_RACOON_MARIO_ATTACK_FROM_RIGHT 3201

#define ID_ANI_MARIO_RACCOON_FALL_RIGHT 12017
#define ID_ANI_MARIO_RACCOON_FALL_LEFT 12018

#define ID_ANI_MARIO_RACCOON_FLY_RIGHT 12025
#define ID_ANI_MARIO_RACCOON_FLY_LEFT 12026

#define ID_ANI_MARIO_RACCOON_FALL_FLY_RIGHT 12027
#define ID_ANI_MARIO_RACCOON_FALL_FLY_LEFT	12028

#define ID_ANI_MARIO_RACCOON_FALL_SLOW_RIGHT 12029
#define ID_ANI_MARIO_RACCOON_FALL_SLOW_LEFT	12030

#define ID_ANI_MARIO_RACCOON_HOLD_IDLE_RIGHT 12019
#define ID_ANI_MARIO_RACCOON_HOLD_IDLE_LEFT 12020
#define ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT 12021
#define ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT 12022

#define ID_ANI_MARIO_RACCOON_HOLD_JUMP_RIGHT 12031
#define ID_ANI_MARIO_RACCOON_HOLD_JUMP_LEFT	12032

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1101

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

#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT 11018
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT 11019
#define	ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT 11020
#define ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT 11021

#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 11024
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 11025
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_LEVEL_RACOON 3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_RACOON_BBOX_WIDTH 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK 1
#define MARIO_UNTOUCHABLE_TIME 2500

#define MARIO_RACCON_ATTACK_TIME_OUT 500

#define POSITION_Y_OF_TAIL_MARIO 18

#define MARIO_POWER_FULL 6
#define POWER_STACK_TIME 250
#define POWER_STACK_LOST_TIME 250
#define LIMIT_MARIO_RACCOON_FLY_TIME 5000
#define MARIO_KICK_TIMEOUT 300
#define MARIO_TRANSFORM_TIME_OUT 1000
#define MARIO_RACOON_TRANSFORM_TIME_OUT 500

#define ADJUST_HEIGHT_MARIO_SMALL_TRANSFORM_BIG 10

class CMario : public CGameObject
{


	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	BOOLEAN isGoThroughBlock = false;
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBackgroundBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();

	int GetAniIdRacoon();

public:


	CGameObject* obj = NULL;
	CTail* tail;
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		this->x = x;
		this->y = y;
		tail = new CTail(x, y);
	}
	BOOLEAN isSitting;
	BOOLEAN isRunning = false;
	BOOLEAN isHoldTurtle = false;
	BOOLEAN isKicking = false;
	BOOLEAN isRunningMax = false;
	BOOLEAN isWalking = false;
	BOOLEAN isFlying = false;
	BOOLEAN isFlapping = false;
	BOOLEAN canFallSlow = false;
	BOOLEAN isTransform = false;
	BOOLEAN isFallSlowing = false;
	BOOLEAN isJumpRunMax;
	BOOLEAN isAdjustHeight = false; //adjust height when transform


	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	int GetLevel() { return level; }
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	boolean IsAttack = false;

	void SetTail();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetCurrentDirection() { return this->nx; }

	int GetCoin() { return coin; }
	void SetCoin(int _coin) { coin = _coin; }

	//Countdown time
	ULONGLONG attack_start = -1;
	ULONGLONG transform_start = -1;
	ULONGLONG die_start = -1;
	ULONGLONG running_start = -1;
	ULONGLONG running_stop = -1;
	ULONGLONG flying_start = -1;
	ULONGLONG kick_start = -1;

	void SetHurt();
	void Decelerate();
	int powerStack = 0;
};