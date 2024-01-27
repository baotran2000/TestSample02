#pragma once
#include "GameObject.h"
#define ID_ANI_P_BUTTON 108
#define ID_ANI_P_BUTTON_IS_PRESSED 109

#define	P_BUTTON_BBOX_WIDTH 16
#define P_BUTTON_BBOX_HEIGHT 16

#define P_BUTTON_IS_PRESSED_BBOX_HEIGHT 11

class PButton : public CGameObject
{
protected:
	float ax;
	float ay;

	BOOLEAN isPressed = false;
	BOOLEAN isGoldBrickTransform = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking();

public:
	PButton(float x, float y);
	void SetIsPressed(BOOLEAN isPressed) { this->isPressed = isPressed; }
	void SetGoldBrickTransform(BOOLEAN isGoldBrickTransform) { this->isGoldBrickTransform = isGoldBrickTransform; }
};

