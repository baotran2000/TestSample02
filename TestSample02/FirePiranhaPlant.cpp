#include "FirePiranhaPlant.h"
#include "Mario.h"
#include "PlayScene.h"
#include "FireBall.h"


FirePiranhaPlant::FirePiranhaPlant(float x, float y, int type)
{
	this->x = x;
	this->y = y;
	this->objType = type;
	this->ax = 0;
	this->ay = 0;
	this->startY = y;

	if (objType == FPP_BIG) {
		this->minY = y - FPP_BIG_BBOX_HEIGHT;
	}
	else {
		this->minY = y - FPP_SMALL_BBOX_HEIGHT;
	}

	SetType(EType::ENEMY);
}

void FirePiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (objType == FPP_BIG) {
		left = x - FPP_BBOX_WIDTH / 2;
		top = y - FPP_BIG_BBOX_HEIGHT / 2;
		right = left + FPP_BBOX_WIDTH;
		bottom = top + FPP_BIG_BBOX_HEIGHT;
	}
	else {
		left = x - FPP_BBOX_WIDTH / 2;
		top = y - FPP_SMALL_BBOX_HEIGHT / 2;
		right = left + FPP_BBOX_WIDTH;
		bottom = top + FPP_SMALL_BBOX_HEIGHT;
	}
}

void FirePiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void FirePiranhaPlant::Render()
{
	int aniId = ID_ANI_FPP_LEFT_BOTTOM;

	if (isBottom) {
		if (objType == FPP_BIG) {
			if (nx > 0) {
				aniId = ID_ANI_FPP_RIGHT_BOTTOM;
			}
			else {
				aniId = ID_ANI_FPP_LEFT_BOTTOM;
			}
		}
		else {
			if (nx > 0) {
				aniId = ID_ANI_FPP_SMALL_RIGHT_BOTTOM;
			}
			else {
				aniId = ID_ANI_FPP_SMALL_LEFT_BOTTOM;
			}
		}
	}
	else {
		if (objType == FPP_BIG) {
			if (nx > 0) {
				aniId = ID_ANI_FPP_RIGHT_TOP;
			}
			else {
				aniId = ID_ANI_FPP_LEFT_TOP;
			}
		}
		else {
			if (nx > 0) {
				aniId = ID_ANI_FPP_SMALL_RIGHT_TOP;
			}
			else {
				aniId = ID_ANI_FPP_SMALL_LEFT_TOP;
			}
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void FirePiranhaPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

bool FirePiranhaPlant::GetSafeZone()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetX() < this->x)
	{
		if (this->x - mario->GetX() <= DISTANCE_SAFE_ZONE)
		{
			return true;
		}
	}
	if (mario->GetX() > this->x)
	{
		if (mario->GetX() - this->x <= DISTANCE_SAFE_ZONE)
		{
			return true;
		}
	}
	return false;
}

void FirePiranhaPlant::ShootFire()
{
	FireBall* fireBall = new FireBall(x, y - ADJUST_FPP_SHOOT_FIRE_BALL_HEIGHT);
	int directionYFireball = 0;
	fireBall->SetDirectionX(nx);
	fireBall->isEnemyShoot = true;
	if (isBottom) {
		fireBall->SetDirectionY(1);
		if (isFar) {
			fireBall->SetState(FIRE_BALL_STATE_FPP_SHOOT_FAR);
		}
		else {
			fireBall->SetState(FIRE_BALL_STATE_FPP_SHOOT_NEAR);
		}
	}
	else {
		fireBall->SetDirectionY(-1);
		if (isFar) {
			fireBall->SetState(FIRE_BALL_STATE_FPP_SHOOT_FAR);
		}
		else {
			fireBall->SetState(FIRE_BALL_STATE_FPP_SHOOT_NEAR);
		}
	}
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->objects.push_back(fireBall);
}