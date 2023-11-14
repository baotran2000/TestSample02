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

FireBall::FireBall(float x, float y) :CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->ay = FIRE_GRAVITY;
}