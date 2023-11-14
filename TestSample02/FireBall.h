#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"

#define FIREBALL_ANI    2203
#define FIRE_BALL_BBOX_WIDTH 9
#define FIRE_BALL_BBOX_HEIGHT 7
#define FIRE_GRAVITY 0.0006f
#define FIRE_BALL_SPEED 0.15f

#define FIRE_BALL_DISAPPEAR_EFFECT_TIME_OUT 200

class FireBall :
	public CGameObject
{
protected:
	float ax, ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
public:
	FireBall(float x, float y);

	BOOLEAN isDisappear = false;
	ULONGLONG start_disappear = -1;
};


