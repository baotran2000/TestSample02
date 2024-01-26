#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "Tail.h"

#include "debug.h"
#include "AssetIDs.h"
#define MARIO_WALKING_SPEED		0.08f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_RUNNING_MAX_SPEED 0.3f
#define MARIO_DECELERATE_SPEED 0.00012f

#define MARIO_ACCEL_WALK_X	0.00015f
#define MARIO_ACCEL_RUN_X	0.00025f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.5f
#define MARIO_ACCEL_JUMP_Y 0.0005f

#define MARIO_JUMP_SPEED_MIN 0.18f
#define MARIO_JUMP_SPEED_MAX 0.28f

#define MARIO_GRAVITY			0.0015f
#define MARIO_JUMP_SPEED_MAX 0.28f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_RACCOON_FLAPPING_SPEED 0.002f
#define MARIO_RACCOON_FALL_SLOW_SPEED 0.03f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_FALL 302

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_RELEASE_RUN 401
#define MARIO_STATE_KICK 402

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_RACOON_STATE_FLY 800
#define MARIO_RACCOON_STATE_FLAPPING 801
#define MARIO_RACCOON_STATE_FALL_SLOW 802

#define MARIO_RACCOON_STATE_ATTACK 900

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

#define MARIO_POWER_FULL 7
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
	boolean isAttack = false;

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	int GetLevel() { return level; }
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	

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