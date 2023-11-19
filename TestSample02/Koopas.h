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
};

