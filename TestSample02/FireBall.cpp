#include "FireBall.h"

void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_BALL_BBOX_WIDTH / 2;
	top = y - FIRE_BALL_BBOX_HEIGHT / 2;
	right = left + FIRE_BALL_BBOX_WIDTH;
	bottom = top + FIRE_BALL_BBOX_HEIGHT;
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FireBall::Render()
{
	int aniId = FIREBALL_ANI;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void FireBall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void FireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->nx != 0)
	{
		SetState(FIRE_BALL_DISAPPEAR);
	}

	if (e->obj->GetType() == ENEMY) {
		e->obj->SetState(ENEMY_STATE_IS_FIRE_ATTACKED);
		SetState(FIRE_BALL_DISAPPEAR);
	}
}

FireBall::FireBall(float x, float y) :CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->ay = FIRE_GRAVITY;
}

void FireBall::SetState(int state)
{
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario_dir = mario->GetCurrentDirection();//Get Mario's current direction

	switch (state)
	{
	/*
	case FIRE_FROM_MARIO:
		vx = mario_dir * FIRE_BALL_SPEED;
		break;
	*/
	case FIRE_BALL_STATE_FPP_SHOOT_NEAR:
		vx = nx * FIRE_BALL_FPP_SHOOT_SPEED_X_NEAR;
		vy = ny * FIRE_BALL_FPP_SHOOT_SPEED_Y;
		isEnemyShoot = true;
		ay = 0;
		break;
	case FIRE_BALL_STATE_FPP_SHOOT_FAR:
		vx = nx * FIRE_BALL_FPP_SHOOT_SPEED_X_FAR;
		vy = ny * FIRE_BALL_FPP_SHOOT_SPEED_Y;
		isEnemyShoot = true;
		ay = 0;
		break;
	case FIRE_BALL_DISAPPEAR:
		vx = 0;
		vy = 0;
		ay = 0;
		start_disappear = GetTickCount64();
		isDisappear = true;
		break;
	}
}

int FireBall::IsCollidable()
{
		return 0;
}