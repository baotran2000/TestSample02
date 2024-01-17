#include "PButton.h"
#include "GoldBrick.h"
#include "PlayScene.h"
#include "MushRoom.h"
#include "GoldBrick.h"

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

	if (isAdjustHeight) {
		y = y + (P_BUTTON_BBOX_HEIGHT - P_BUTTON_IS_PRESSED_BBOX_HEIGHT);
		isAdjustHeight = false;
	}

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isPressed) {
		for (size_t i = 0; i < scene->objects.size(); i++) {
			if (scene->objects[i]->GetType() == GOLDBRICK) {
				GoldBrick* goldbrick = dynamic_cast<GoldBrick*>(scene->objects[i]);
				if (goldbrick->GetModel() == GOLD_BRICK_COIN) {
					goldbrick->SetState(GOLD_BRICK_STATE_TRANSFORM_COIN);
				}
			}
		}
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
	RenderBoundingBox();
}