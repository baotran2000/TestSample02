#pragma once
#include "GameObject.h"

#define GOLD_BRICK_BBOX_WIDTH 16
#define GOLD_BRICK_BBOX_HEIGHT 16

#define ID_ANI_GOLD_BRICK 104
#define ID_ANI_GOLD_BRICK_EMPTY 103
#define ID_ANI_COIN_IDLE 113

#define GOLD_BRICK_SPEED_UP 0.1f
#define GOLD_BRICK_SPEED_DOWN 0.1f

#define GOLD_BRICK_MUSHROOM 1
#define GOLD_BRICK_P_BUTTON 2
#define GOLD_BRICK_COIN 3

#define GOLD_BRICK_STATE_UP 100
#define GOLD_BRICK_STATE_TRANSFORM_COIN 200
#define GOLD_BRICK_STATE_NORMAL 300

#define GOLD_BRICK_COIN_TIME_OUT 5000

class GoldBrick : public CGameObject
{
protected:
	float ax;
	float ay;
	float minY;
	float startY;
	float startX;

	BOOLEAN isTransform = false;
	BOOLEAN isBreak = false;
	ULONGLONG transform_start = -1;
	// model = 1: ra nam xanh
	// model = 2: ra P button
	// model = 3: ra tien

	vector<LPGAMEOBJECT> objects;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void OnNoCollision(DWORD dt);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsBlocking();
public:
	GoldBrick(float x, float y, int model);
	virtual void SetState(int state);
	BOOLEAN isUnbox = false;
	BOOLEAN isEmpty = false;
	void SetBreak(int isBreak) { this->isBreak = isBreak; }
};

