#include "GoldBrick.h"
#include "PlayScene.h"
#include "Mushroom.h"
#include "PButton.h"
#include "Break.h"

GoldBrick::GoldBrick(float x, float y, int model) :CGameObject(x, y)
{
	this->objType = model;

	this->ay = 0;
	this->ax = 0;
	this->minY = y - GOLD_BRICK_BBOX_HEIGHT;
	this->startY = y;
	this->startX = x;

	SetType(EType::GOLDBRICK);
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
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		vy = GOLD_BRICK_SPEED_DOWN;
		if (mario->GetLevel() != MARIO_LEVEL_SMALL) 
		{
			if (objType == GOLD_BRICK_COIN) {
				isBreak = true;
			}
		}
	}
	if (y > startY)
	{
		y = startY;
		vy = 0;
		if (mario->GetLevel() != MARIO_LEVEL_SMALL) 
		{
			isEmpty = true;
			isUnbox = true;
		}
	}

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isUnbox) 
	{
		if (objType == GOLD_BRICK_MUSHROOM) {
			CMushroom* mushroom = new CMushroom(x, y, GREEN_MUSHROOM);
			mushroom->SetState(MUSHROOM_STATE_UP);
			scene->objects.insert(scene->objects.begin() + 1, mushroom);
		}
		if (objType == GOLD_BRICK_P_BUTTON) {
			PButton* button = new PButton(x, y - P_BUTTON_BBOX_HEIGHT);
			scene->objects.insert(scene->objects.begin() + 1, button);
		}
		isUnbox = false;
	}

	if (isBreak) 
	{
		CBreak* break1 = new CBreak(x, y);
		break1->SetState(BREAK_STATE_TOP_RIGHT);
		CBreak* break2 = new CBreak(x, y);
		break2->SetState(BREAK_STATE_TOP_LEFT);
		CBreak* break3 = new CBreak(x, y);
		break3->SetState(BREAK_STATE_BOTTOM_RIGHT);
		CBreak* break4 = new CBreak(x, y);
		break4->SetState(BREAK_STATE_BOTTOM_LEFT);
		scene->objects.insert(scene->objects.begin() + 1, break1);
		scene->objects.insert(scene->objects.begin() + 1, break2);
		scene->objects.insert(scene->objects.begin() + 1, break3);
		scene->objects.insert(scene->objects.begin() + 1, break4);
		isDeleted = true;
		isBreak = false;
	}

	if (isTransform && GetTickCount64() - transform_start > GOLD_BRICK_COIN_TIME_OUT) 
	{
		SetState(GOLD_BRICK_STATE_NORMAL);
		isTransform = false;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

int GoldBrick::IsBlocking() 
{
	if (state == GOLD_BRICK_STATE_TRANSFORM_COIN) 
	{
		return 0;
	}
	else
		return 1;

}

void GoldBrick::Render()
{
	int aniId = ID_ANI_GOLD_BRICK;

	if (objType != GOLD_BRICK_COIN) {
		if (isEmpty) {
			aniId = ID_ANI_GOLD_BRICK_EMPTY;
		}
	}
	else {
		if (isTransform) {
			aniId = ID_ANI_COIN_IDLE;
		}
		else {
			aniId = ID_ANI_GOLD_BRICK;
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void GoldBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOLD_BRICK_STATE_UP:
		vy = -GOLD_BRICK_SPEED_UP;
		break;
	case GOLD_BRICK_STATE_TRANSFORM_COIN:
		if (type == GOLDBRICK) {
			SetType(EType::COIN);
			transform_start = GetTickCount64();
			isTransform = true;
		}
		break;
	case GOLD_BRICK_STATE_NORMAL:
		if (type == COIN) {
			DebugOut(L"[INFO] mario raccoon fly time end\n");
			SetType(EType::GOLDBRICK);
			transform_start = -1;
			isTransform = false;
		}
		break;
	}
}