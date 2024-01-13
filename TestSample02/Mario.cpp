#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "PlayScene.h"
#include "Collision.h"
#include "BGBlock.h"
#include "QuestionBrick.h"
#include "Leaf.h"
#include "FirePiranhaPlant.h"
#include "FireBall.h"
#include "Koopas.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (vy <= -MARIO_JUMP_RUN_SPEED_Y && isRunningMax)
	{
		vy = -MARIO_JUMP_RUN_SPEED_Y;
		ay = MARIO_GRAVITY;
	}
	//change direction when run max speed
	
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (vy < 0)
	{
		isOnPlatform = false;
	}

	if (level == MARIO_LEVEL_BIG && GetTickCount64() - transform_start > MARIO_TRANSFORM_TIME_OUT && isTransform)
	{
		isTransform = false;
		transform_start = -1;
	}

	if (level == MARIO_LEVEL_RACOON && GetTickCount64() - transform_start > MARIO_RACOON_TRANSFORM_TIME_OUT && isTransform)
	{
		isTransform = false;
		transform_start = -1;
	}

	if (isTransform) 
	{
		ay = 0;
		vx = 0;
	}

	if (isGoThroughBlock) 
	{
		y -= ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK;
		vy = -MARIO_JUMP_SPEED_MAX;
		isGoThroughBlock = false;
	}

	if (IsAttack) {
		SetTail();
	}
	if (tail) {
		tail->Update(dt, coObjects);
	}
	if (IsAttack && GetTickCount64() - attack_start > MARIO_RACCON_ATTACK_TIME_OUT) 
	{
		IsAttack = false;
		attack_start = -1;
		tail = NULL;
	}

	if (GetTickCount64() - kick_start > MARIO_KICK_TIMEOUT && isKicking) 
	{
		isKicking = false;
		kick_start = -1;
	}
	
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::SetTail()
{
	if (!tail) {
		tail = new CTail(x, y);
	}
	if (nx > 0)
	{
		tail->SetPosition(x - TAIL_BBOX_WIDTH / 2, y + POSITION_Y_OF_TAIL_MARIO / 2 - TAIL_BBOX_HEIGHT / 2);
	}
	else {
		tail->SetPosition(x + MARIO_BIG_BBOX_WIDTH - TAIL_BBOX_WIDTH / 2, y + POSITION_Y_OF_TAIL_MARIO / 2 - TAIL_BBOX_HEIGHT / 2);
	}
	tail->SetWidth(TAIL_BBOX_WIDTH);
	tail->SetHeight(TAIL_BBOX_HEIGHT);
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
		if (e->ny < 0)
		{
			isOnPlatform = true;
		}
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBGBlock*>(e->obj))
		OnCollisionWithBackgroundBlock(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<FirePiranhaPlant*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<FireBall*>(e->obj))
		OnCollisionWithFireball(e);
	else if (dynamic_cast<Koopas*>(e->obj))
		OnCollisionWithKoopas(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			if (goomba->GetType() == NORMAL_GOOMBA) {
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else
			{
				if (goomba->GetState() == GOOMBA_STATE_WALKING) {
					goomba->SetState(GOOMBA_STATE_DIE);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else
				{
					goomba->SetState(GOOMBA_STATE_WALKING);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
			}
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

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithBackgroundBlock(LPCOLLISIONEVENT e)
{
	CBGBlock* block = dynamic_cast<CBGBlock*>(e->obj);
	if (e->ny > 0) {
		isGoThroughBlock = true;
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny > 0 && !questionBrick->isEmpty) {
		questionBrick->SetState(QUESTION_BRICK_STATE_UP);
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	DebugOut(L"-------------------------------------------------------");
	//level = MARIO_LEVEL_RACOON;
	e->obj->Delete();
}

void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	if (e->nx != 0 || e->ny != 0) {
		SetHurt();
	}
}

void CMario::OnCollisionWithFireball(LPCOLLISIONEVENT e)
{
	FireBall* fireball = dynamic_cast<FireBall*>(e->obj);
	if (fireball->isEnemyShoot) {
		SetHurt();
	}
}

void CMario::SetHurt()
{
	if (untouchable == 0) {
		if (level > MARIO_LEVEL_SMALL) {
			level--;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
			die_start = GetTickCount64();
		}
	}
	else return;
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	Koopas* koopas = dynamic_cast<Koopas*>(e->obj);

	if (e->ny < 0)
	{
		if (koopas->GetState() == KOOPAS_STATE_IS_KICKED) {
			if (koopas->isDefend) {
				koopas->SetState(KOOPAS_STATE_DEFEND);
			}
			else {
				koopas->SetState(KOOPAS_STATE_UPSIDE);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_WALKING)
		{
			koopas->SetState(KOOPAS_STATE_DEFEND);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_JUMP) {
			koopas->SetState(KOOPAS_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_DEFEND || koopas->GetState() == KOOPAS_STATE_UPSIDE)
		{
			koopas->SetState(KOOPAS_STATE_IS_KICKED);
		}
	}
	else if (e->nx != 0)
	{
		if (koopas->GetState() == KOOPAS_STATE_DEFEND || koopas->GetState() == KOOPAS_STATE_UPSIDE) {
			if (isRunning && !isHoldTurtle) 
			{
				isHoldTurtle = true;
				isKicking = false;
				koopas->isHeld = true;
			}
			else {
				SetState(MARIO_STATE_KICK);
				koopas->SetState(KOOPAS_STATE_IS_KICKED);
			}
		}
		else {
			SetHurt();
		}
	}
	else if (e->ny > 0) {
		SetHurt();
	}
}

//
// Get animation ID for small Mario
//
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
			if (isHoldTurtle) 
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
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
		else if (vx == 0)
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
		else if (vx < 0)
		{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
		}
		else if (isHoldTurtle) 
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
			}
			else if (vx > 0) {
				aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT;
			}
			else {
				aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
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
			if (isHoldTurtle) 
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
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
		else if (isHoldTurtle) 
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
			}
			else if (vx > 0) {
				aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
			}
			else {
				aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
			}
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

//
// Get animation ID for Raccoon Mario
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_RACOON_MARIO_JUMP_RUN_LEFT;
		}
		else 
		{
			if (isHoldTurtle) 
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_HOLD_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_HOLD_JUMP_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_RACOON_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_RACOON_MARIO_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_RACOON_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_RACOON_MARIO_SIT_LEFT;
		}
		else if (IsAttack) {
			if (nx > 0) {
				aniId = ID_ANI_RACOON_MARIO_ATTACK_FROM_LEFT;
			}
			else
				aniId = ID_ANI_RACOON_MARIO_ATTACK_FROM_RIGHT;
		}
		else if (isHoldTurtle) 
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_HOLD_IDLE_LEFT;
			}
			else if (vx > 0) {
				aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT;
			}
			else {
				aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT;
			}
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_RACOON_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_RACOON_MARIO_IDLE_LEFT;
			}

			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_RACOON_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOON_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOON_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_RACOON_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOON_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOON_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_RACOON_MARIO_IDLE_RIGHT;
	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();


	animations->Get(aniId)->Render(x, y);

	if (tail) {
		tail->Render();
	}

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		isRunning = true;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		isRunning = true;
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
			{
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			}
			else
				vy = -MARIO_JUMP_SPEED_Y;
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
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_RACOON_ATTACK:
		IsAttack = true;
		attack_start = GetTickCount64();
		break;

	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level>=MARIO_LEVEL_BIG)
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
			if (level == MARIO_LEVEL_RACOON) {
				left = x - MARIO_RACOON_BBOX_WIDTH / 2;
				right = left + MARIO_RACOON_BBOX_WIDTH;
			}
			else {
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
				right = left + MARIO_BIG_BBOX_WIDTH;
			}
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
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
	if (this->level == MARIO_LEVEL_RACOON)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::Decelerate()
{
	if (vx > 0)
	{
		ax = -MARIO_DECELERATE_SPEED;
	}
	if (vx < 0)
	{
		ax = MARIO_DECELERATE_SPEED;
	}
}

