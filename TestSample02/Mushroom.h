#pragma once
#include "GameObject.h"

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define ID_ANI_RED_MUSHROOM	105
#define ID_ANI_GREEN_MUSHROOM 106

#define MUSHROOM_RUN_SPEED 0.08f
#define MUSHROOM_GRAVITY 0.003f

#define MUSHROOM_STATE_UP 100
#define MUSHROOM_STATE_RUN 200

#define MUSHROOM_SPEED_UP 0.03f

#define RED_MUSHROOM 1
#define GREEN_MUSHROOM 2

class CMushroom :
	public CGameObject
{
protected:
	float ax;
	float ay;
	float minY;
public:
	CMushroom(float x, float y, int model);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 1; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

