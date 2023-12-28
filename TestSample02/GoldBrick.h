#pragma once
#include "GameObject.h"

#define GOLD_BRICK_BBOX_WIDTH 16
#define GOLD_BRICK_BBOX_HEIGHT 16

class GoldBrick : public CGameObject
{
protected:
	float ax;
	float ay;
	float minY;
	float startY;
	float startX;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void OnNoCollision(DWORD dt);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	GoldBrick(float x, float y, int model);
};

