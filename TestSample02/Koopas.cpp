#include "Koopas.h"
#include "Utils.h"
#include "BGBlock.h"
#include "PlayScene.h"
#include "Mario.h"
#include "QuestionBrick.h"
#include "Goomba.h"
#include "GoldBrick.h"

Koopas::Koopas(float x, float y, int model) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->objType = model;
	SetType(EType::ENEMY);
	defend_start = -1;
	isHeld = false;
	if (model == KOOPAS_GREEN_WING) 
	{
		SetState(KOOPAS_STATE_JUMP);
	}
	else 
	{
		SetState(KOOPAS_STATE_WALKING);
	}
}

void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDefend || isUpside) 
	{

		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DEFEND / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DEFEND;
	}
	else 
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera(this)) return;
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->isHoldTurtle && isHeld)
	{
		if (mario->GetDirection() > 0) 
		{
			x = mario->GetX() + KOOPAS_POSITION_ABSOLUTE_MARIO;
			y = mario->GetY();
		}
		else {
			x = mario->GetX() - KOOPAS_POSITION_ABSOLUTE_MARIO;
			y = mario->GetY();
		}
		ay = 0;
		isHeld = true;
	}
	else 
	{
		if (isHeld)
		{
			ay = KOOPAS_GRAVITY;
			SetState(KOOPAS_STATE_IS_KICKED);
		}
	}

	// start animation comeback
	if (GetTickCount64() - defend_start > KOOPAS_COMBACK_START && (isDefend || isUpside) && !isKicked) 
	{
		isComeback = true;
	}

	// end defend and start walking
	if (GetTickCount64() - defend_start > KOOPAS_DEFEND_TIMEOUT && (isDefend || isUpside) && !isKicked) 
	{
		SetState(KOOPAS_STATE_WALKING);
		defend_start = -1;
		vy = -KOOPAS_COMBACK_HEIGHT_ADJUST;

		if (mario->isHoldTurtle) 
		{
			mario->isHoldTurtle = false;
			mario->SetHurt();
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Koopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;

	if (objType == KOOPAS_GREEN_WING) {
		if (vx > 0) {
			aniId = ID_ANI_KOOPAS_GREEN_WING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPAS_GREEN_WING_LEFT;
		}
	}
	if (objType == KOOPAS_GREEN || objType == KOOPAS_GREEN_WING)
	{
		if (state == ENEMY_STATE_IS_KOOPAS_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED) {
			aniId = ID_ANI_KOOPAS_IS_UPSIDE;
		}
		if (vx > 0)
		{
			if (state == KOOPAS_STATE_WALKING)
			{
				aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
			}
			else if (isKicked)
			{
				if (isDefend)
				{
					aniId = ID_ANI_KOOPAS_IS_KICKED;
				}
				else if (isUpside)
				{
					aniId = ID_ANI_KOOPAS_UPSIDE_ISKICKED;
				}
			}
		}
		else
		{
			if (state == KOOPAS_STATE_WALKING)
			{
				aniId = ID_ANI_KOOPAS_WALKING_LEFT;
			}
			else if (isKicked)
			{
				if (isDefend)
				{
					aniId = ID_ANI_KOOPAS_IS_KICKED;
				}
				else if (isUpside)
				{
					aniId = ID_ANI_KOOPAS_UPSIDE_ISKICKED;
				}
			}
		}
		if (!isKicked)
		{
			if (isDefend)
			{
				if (isComeback)
				{
					aniId = ID_ANI_KOOPAS_COMEBACK;
				}
				else
				{
					aniId = ID_ANI_KOOPAS_DEFEND;
				}
			}
			else if (isUpside)
			{
				if (isComeback)
				{
					aniId = ID_ANI_KOOPAS_UPSIDE_COMEBACK;
				}
				else
				{
					aniId = ID_ANI_KOOPAS_IS_UPSIDE;
				}
			}
		}
	}
	else if (objType == KOOPAS_RED)
	{
		if (state == ENEMY_STATE_IS_KOOPAS_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED) 
		{
			aniId = ID_ANI_KOOPAS_RED_IS_UPSIDE;
		}
		if (vx > 0)
		{
			if (state == KOOPAS_STATE_WALKING)
			{
				aniId = ID_ANI_KOOPAS_RED_WALKING_RIGHT;
			}
			else if (isKicked)
			{
				if (isDefend)
				{
					aniId = ID_ANI_KOOPAS_RED_IS_KICKED;
				}
				else if (isUpside)
				{
					aniId = ID_ANI_KOOPAS_RED_UPSIDE_ISKICKED;
				}
			}
		}
		else
		{
			if (state == KOOPAS_STATE_WALKING)
			{
				aniId = ID_ANI_KOOPAS_RED_WALKING_LEFT;
			}
			else if (isKicked)
			{
				if (isDefend)
				{
					aniId = ID_ANI_KOOPAS_RED_IS_KICKED;
				}
				else if (isUpside)
				{
					aniId = ID_ANI_KOOPAS_RED_UPSIDE_ISKICKED;
				}
			}
		}
		if (!isKicked)
		{
			if (isDefend)
			{
				if (isComeback)
				{
					aniId = ID_ANI_KOOPAS_RED_COMEBACK;
				}
				else
				{
					aniId = ID_ANI_KOOPAS_RED_DEFEND;
				}
			}
			else if (isUpside)
			{
				if (isComeback)
				{
					aniId = ID_ANI_KOOPAS_RED_UPSIDE_COMEBACK;
				}
				else
				{
					aniId = ID_ANI_KOOPAS_RED_IS_UPSIDE;
				}
			}
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

int Koopas::IsCollidable()
{
	if (state == ENEMY_STATE_IS_KOOPAS_ATTACKED) 
	{
		return 0;
	}
	else {
		return 1;
	}
}

void Koopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Koopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		vy = 0;

		if (isTailAttacked) 
		{
			SetState(KOOPAS_STATE_UPSIDE);
			vy = -KOOPAS_BOUNCE_SPEED;
			isTailAttacked = false;
		}
		else {
			if (objType == KOOPAS_GREEN_WING && state == KOOPAS_STATE_JUMP) 
			{
				vy = -KOOPAS_WING_JUMP_SPEED;
				ay = KOOPAS_WING_GRAVITY;
			}
		}
	}
	else if (e->nx != 0)
	{
		if (e->obj->GetModel() == OBJECT || e->obj->GetModel() == GOLDBRICK) 
		{
			vx = -vx;
		}
	}
	if (e->obj->GetType() == ENEMY) {
		if (e->obj->GetState() != ENEMY_STATE_IS_KOOPAS_ATTACKED) 
		{
			if (state == KOOPAS_STATE_IS_KICKED) 
			{
				e->obj->SetState(ENEMY_STATE_IS_KOOPAS_ATTACKED);
			}
		}
	}

	if (dynamic_cast<CBGBlock*>(e->obj))
		OnCollisionWithBackGroundBlock(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<GoldBrick*>(e->obj))
		OnCollisionWithGoldBrick(e);
}

void Koopas::OnCollisionWithGoldBrick(LPCOLLISIONEVENT e)
{
	GoldBrick* goldbrick = dynamic_cast<GoldBrick*>(e->obj);

	if (e->nx != 0 && goldbrick->GetType() == GOLD_BRICK_COIN) 
	{
		if (goldbrick->GetState() != GOLD_BRICK_STATE_TRANSFORM_COIN) 
		{
			if (state == KOOPAS_STATE_IS_KICKED) 
			{
				goldbrick->SetBreak(true);
			}
		}
	}

	if (model == KOOPAS_RED) {
		if (e->ny < 0) {
			if (state == KOOPAS_STATE_WALKING && model == KOOPAS_RED) {
				if (x <= goldbrick->GetX() - ADJUST_X_TO_RED_CHANGE_DIRECTION)
				{
					vy = 0;
					vx = KOOPAS_WALKING_SPEED;
				}
				else if (x >= goldbrick->GetX() + ADJUST_X_TO_RED_CHANGE_DIRECTION) {
					vy = 0;
					vx = -KOOPAS_WALKING_SPEED;
				}
			}
		}
	}
}

void Koopas::OnCollisionWithBackGroundBlock(LPCOLLISIONEVENT e)
{
	CBGBlock* block = dynamic_cast<CBGBlock*>(e->obj);

	if (e->ny < 0) {
		if (state == KOOPAS_STATE_WALKING && model == KOOPAS_RED) {
			if (x <= block->GetX() - block->GetWidth() / 2)
			{
				vy = 0;
				vx = KOOPAS_WALKING_SPEED;
			}
			else if (x >= block->GetX() + block->GetWidth() / 2) {
				vy = 0;
				vx = -KOOPAS_WALKING_SPEED;
			}
		}
	}

}

void Koopas::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);

	if (e->nx != 0 && !questionBrick->isEmpty) {
		if (state == KOOPAS_STATE_IS_KICKED) {
			questionBrick->SetState(QUESTION_BRICK_STATE_UP);
			vx = -vx;
		}
	}
}

void Koopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	if (state == KOOPAS_STATE_IS_KICKED) {
		e->obj->SetState(ENEMY_STATE_IS_KOOPAS_ATTACKED);
	}
}

void Koopas::SetState(int state)
{
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		vy = 0;
		ay = KOOPAS_GRAVITY;
		isComeback = false;
		isDefend = false;
		isUpside = false;
		isKicked = false;
		isHeld = false;
		break;
	case KOOPAS_STATE_DEFEND:
		isDefend = true;
		isComeback = false;
		isKicked = false;
		isUpside = false;
		defend_start = GetTickCount64();
		vx = 0;
		break;
	case KOOPAS_STATE_UPSIDE:
		isUpside = true;
		isDefend = false;
		isComeback = false;
		isKicked = false;
		defend_start = GetTickCount64();
		vx = 0;
		break;
	case KOOPAS_STATE_IS_KICKED:
		isKicked = true;
		isHeld = false;
		vx = mario->GetDirection() * KOOPAS_IS_KICKED_SPEED;
		break;
	case KOOPAS_STATE_JUMP:
		vx = KOOPAS_RED_WING_SPEED_X;
		isComeback = false;
		isDefend = false;
		isUpside = false;
		isKicked = false;
		break;
	case ENEMY_STATE_IS_KOOPAS_ATTACKED:
		ay = KOOPAS_GRAVITY;
		vx = 0;
		break;
	case ENEMY_STATE_IS_TAIL_ATTACKED:
		ay = KOOPAS_GRAVITY;
		vy = -KOOPAS_SPEED_Y_IS_TAIL_ATTACKED;
		vx = mario->GetDirection() * KOOPAS_SPEED_X_IS_TAIL_ATTACKED;
		isTailAttacked = true;
		break;
	}
}

