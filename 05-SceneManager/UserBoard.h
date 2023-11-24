#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "CountdownTimer.h"

#define ID_ANI_BOARD 10400
#define ID_ANI_CARD 10401

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

#define ID_ANI_P_MARK_NORMAL 10020
#define ID_ANI_P_MARK_ACTIVE 10021
#define ID_ANI_ARROW_NORMAL 10022
#define ID_ANI_ARROW_ACTIVE 10023

#define ID_ANI_M_MARK 10022


class CUserBoard : public CGameObject {
	static CUserBoard* __instance;
	int countdown = 000;
	vector<int> vpoint;
	vector<int> vcoin;
	vector<int> vlife;
	vector<int> vtime;
	ULONGLONG loop_start;

	int getAniId(int num);
	void translateNumberToSprite();

public:	
	CUserBoard(float x, float y) : CGameObject(x, y) {
		loop_start = -1;

	}
	void Render();

	void RenderBoundingBox();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	static CUserBoard* GetInstance();
};