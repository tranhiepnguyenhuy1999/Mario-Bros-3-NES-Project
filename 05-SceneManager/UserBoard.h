#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "CountdownTimer.h"

#define ID_ANI_BOARD 10005
#define ID_ANI_NUMBER0 10010
#define ID_ANI_NUMBER1 10011
#define ID_ANI_NUMBER2 10012
#define ID_ANI_NUMBER3 10013
#define ID_ANI_NUMBER4 10014
#define ID_ANI_NUMBER5 10015
#define ID_ANI_NUMBER6 10016
#define ID_ANI_NUMBER7 10017
#define ID_ANI_NUMBER8 10018
#define ID_ANI_NUMBER9 10019

#define ID_ANI_NUMBERLEFT 10020
#define ID_ANI_NUMBERP 10021

class CUserBoard : public CGameObject {
	static CUserBoard* __instance;
	int point, coin, life;
	vector<int> pointA;
	vector<int> coinA;
	vector<int> lifeA;
	vector<int> timeA;
public:
	CUserBoard(float x, float y) : CGameObject(x, y) {
		CountdownTimer* timer = new CountdownTimer();
	}
	void translateNumberToSprite();
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetValue(int point, int coin, int life);
	int getAniId(int num);
	static CUserBoard* GetInstance();
};