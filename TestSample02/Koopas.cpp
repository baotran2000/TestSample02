#include "Koopas.h"
#include "Utils.h"
#include "BGBlock.h"

Koopas::Koopas(float x, float y, int model) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->objType = model;
	SetType(EType::ENEMY);
}

void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPAS_BBOX_WIDTH / 2;
	top = y - KOOPAS_BBOX_HEIGHT / 2;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT;
}

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Render();
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
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

		if (isTailAttacked) {
			SetState(KOOPAS_STATE_UPSIDE);
			vy = -KOOPAS_BOUNCE_SPEED;
			isTailAttacked = false;
		}
		else {
			if (objType == KOOPAS_GREEN_WING && state == KOOPAS_STATE_JUMP) {
				vy = -KOOPAS_WING_JUMP_SPEED;
				ay = KOOPAS_WING_GRAVITY;
			}
		}
	}
	else if (e->nx != 0)
	{
		if (e->obj->GetModel() == OBJECT || e->obj->GetModel() == GOLDBRICK) {
			vx = -vx;
		}
	}

	if (dynamic_cast<CBGBlock*>(e->obj))
		OnCollisionWithBackGroundBlock(e);
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
	if (e->nx != 0) {
		if (state == KOOPAS_STATE_IS_KICKED) {
			vx = -vx;
			nx = -nx;
		}
	}
}