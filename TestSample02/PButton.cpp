#include "PButton.h"
#include "GoldBrick.h"
#include "PlayScene.h"
#include "MushRoom.h"

PButton::PButton(float x, float y) :CGameObject(x, y)
{
	this->ay = 0;
	this->ax = 0;
}

void PButton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - P_BUTTON_BBOX_WIDTH / 2;
	top = y - P_BUTTON_BBOX_HEIGHT / 2;
	right = left + P_BUTTON_BBOX_WIDTH;
	bottom = top + P_BUTTON_BBOX_HEIGHT;
	if (isPressed) {
		left = top = right = bottom = 0;
	}
}

int PButton::IsCollidable() {
	if (isPressed) {
		return 0;
	}
	else {
		return 1;
	}
}

int PButton::IsBlocking() {
	if (isPressed) {
		return 0;
	}
	else {
		return 1;
	}
}


void PButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isGoldBrickTransform) 
	{
		y = y + (P_BUTTON_BBOX_HEIGHT - P_BUTTON_IS_PRESSED_BBOX_HEIGHT);

		CGame::GetInstance()->transform = true;
		isGoldBrickTransform = false;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void PButton::Render()
{
	int aniId = ID_ANI_P_BUTTON;

	if (isPressed) {
		aniId = ID_ANI_P_BUTTON_IS_PRESSED;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}