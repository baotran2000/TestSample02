#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26

#define KOOPAS_GREEN 1
#define KOOPAS_RED 2
#define KOOPAS_GREEN_WING 3

#define ID_ANI_KOOPAS_WALKING_RIGHT 40001

#define ID_ANI_KOOPAS_GREEN_WING_RIGHT 40009
#define ID_ANI_KOOPAS_GREEN_WING_LEFT 40010

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DEFEND 200
#define KOOPAS_STATE_IS_KICKED 300
#define KOOPAS_STATE_UPSIDE 400
#define KOOPAS_STATE_JUMP 500

#define KOOPAS_BOUNCE_SPEED 0.3f

#define KOOPAS_WING_JUMP_SPEED 0.15f
#define KOOPAS_WING_GRAVITY 0.0002f

#define KOOPAS_WALKING_SPEED 0.02f

#define KOOPAS_BBOX_HEIGHT_DEFEND 16

#define KOOPAS_DEFEND_TIMEOUT 8000
#define KOOPAS_COMBACK_START 6000

#define KOOPAS_COMBACK_HEIGHT_ADJUST 0.15f

class Koopas :
	public CGameObject
{	
protected:
	float ax;
	float ay;

	vector<LPGAMEOBJECT> effects;
public:
	Koopas(float x, float y, int model);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);

	BOOLEAN isTailAttacked = false;
	BOOLEAN isHeld;
	BOOLEAN isDefend;
	BOOLEAN isUpside;


	ULONGLONG defend_start;

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithBackGroundBlock(LPCOLLISIONEVENT e);
};

