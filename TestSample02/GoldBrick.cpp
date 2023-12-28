#include "GoldBrick.h"

GoldBrick::GoldBrick(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;

	this->ay = 0;
	this->ax = 0;
	this->minY = y - GOLD_BRICK_BBOX_HEIGHT;
	this->startY = y;
	this->startX = x;
}

void GoldBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - GOLD_BRICK_BBOX_WIDTH / 2;
	top = y - GOLD_BRICK_BBOX_HEIGHT / 2;
	right = left + GOLD_BRICK_BBOX_WIDTH;
	bottom = top + GOLD_BRICK_BBOX_HEIGHT;
}

void GoldBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void GoldBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void GoldBrick::Render()
{

}