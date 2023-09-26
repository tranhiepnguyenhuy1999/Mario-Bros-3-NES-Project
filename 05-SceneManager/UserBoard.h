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

#define ID_ANI_NUMBER_BLACK_LEFT 10020
#define ID_ANI_NUMBER_BLACK_P 10021
#define ID_ANI_NUMBER_WHITE_LEFT 10022
#define ID_ANI_NUMBER_WHITE_P 10023

#define ID_PROP_POINT 1
#define ID_PROP_LIFE 2 
#define ID_PROP_COIN 3
#define ID_PROP_FLY_MARK 4 

class CUserBoard : public CGameObject {
	static CUserBoard* __instance;
	int coin, life, fly_mark, countdown;
	double point;
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
		fly_mark = 0;
		point = 0;
		coin = 0;
		life = 0;
		countdown = 000;
	}
	void Render();
	void startCount() {
		loop_start = GetTickCount64();
	}
	void updateProps(int key, int val) { 
		switch (key)
		{
		case ID_PROP_POINT:
			point += val;
			break;
		case ID_PROP_LIFE:
			life += val;
			break;
		case ID_PROP_COIN:
			coin += val;
			break;
		case ID_PROP_FLY_MARK:
			fly_mark += val;
			break;
		default:
			break;
		}
	}

	void RenderBoundingBox();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};

	static CUserBoard* GetInstance();
};