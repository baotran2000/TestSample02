﻿#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26

#define KOOPAS_GREEN 1
#define KOOPAS_RED 2
#define KOOPAS_GREEN_WING 3

// KOOPAS GREEN
#define ID_ANI_KOOPAS_WALKING_RIGHT 40001
#define ID_ANI_KOOPAS_WALKING_LEFT 40002
#define ID_ANI_KOOPAS_DEFEND 40003
#define ID_ANI_KOOPAS_IS_KICKED 40004
#define ID_ANI_KOOPAS_IS_UPSIDE 40005
#define ID_ANI_KOOPAS_COMEBACK 40006
#define ID_ANI_KOOPAS_UPSIDE_ISKICKED 40007	
#define ID_ANI_KOOPAS_UPSIDE_COMEBACK 40008 
#define ID_ANI_KOOPAS_GREEN_WING_RIGHT 40009
#define ID_ANI_KOOPAS_GREEN_WING_LEFT 40010

// KOOPAS RED
#define ID_ANI_KOOPAS_RED_WALKING_RIGHT 40011
#define ID_ANI_KOOPAS_RED_WALKING_LEFT 40012
#define ID_ANI_KOOPAS_RED_DEFEND 40013
#define ID_ANI_KOOPAS_RED_IS_KICKED 40014
#define ID_ANI_KOOPAS_RED_IS_UPSIDE 40015
#define ID_ANI_KOOPAS_RED_COMEBACK 40016
#define ID_ANI_KOOPAS_RED_UPSIDE_ISKICKED 40017 
#define ID_ANI_KOOPAS_RED_UPSIDE_COMEBACK 40018 

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

#define KOOPAS_IS_KICKED_SPEED 0.18f
#define KOOPAS_SPEED_Y_IS_TAIL_ATTACKED 0.4f
#define KOOPAS_SPEED_X_IS_TAIL_ATTACKED 0.05f
#define KOOPAS_RED_WING_SPEED_X 0.03f
#define ADJUST_POSITION_KOOPAS_HELD 13
#define KOOPAS_POSITION_ABSOLUTE_MARIO 14

#define KOOPAS_DEFEND_TIMEOUT 8000 
#define KOOPAS_COMBACK_START 6000 

#define ADJUST_X_TO_RED_CHANGE_DIRECTION 10

class Koopas :
	public CGameObject
{	
protected:
	float ax;
	float ay;

	vector<LPGAMEOBJECT> effects;

	int mario_nx;

public:
	Koopas(float x, float y, int model);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable();

	BOOLEAN isTailAttacked = false;
	BOOLEAN isHeld;
	BOOLEAN isDefend;
	BOOLEAN isUpside;
	BOOLEAN isKicked;
	BOOLEAN isComeback;


	ULONGLONG defend_start;

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithBackGroundBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	virtual void SetState(int state);
};

