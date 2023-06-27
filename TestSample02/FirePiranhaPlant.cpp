#include "FirePiranhaPlant.h"
FirePiranhaPlant::FirePiranhaPlant(float x, float y, int type)
{
	this->x = x;
	this->y = y;
	this->objType = type;
	this->ax = 0;
	this->ay = 0;
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