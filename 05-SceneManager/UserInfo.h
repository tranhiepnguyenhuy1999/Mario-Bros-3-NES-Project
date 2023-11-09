#pragma once
using namespace std;
#include <Windows.h>

#define ID_PROPS_POINT 1
#define ID_PROPS_LIFE 2 
#define ID_PROPS_COIN 3
#define ID_PROPS_FLY_MARK 4 

class UserInfo
{
	static UserInfo* __instance;
	int coin, life, fly_mark;
	int point;
public:
	UserInfo() {
		fly_mark = 0;
		point = 0;
		coin = 0;
		life = 0;
	}
	void updateProps(int key, int val) {
		switch (key)
		{
		case ID_PROPS_POINT:
			point += val;
			break;
		case ID_PROPS_LIFE:
			life += val;
			break;
		case ID_PROPS_COIN:
			coin += val;
			break;
		case ID_PROPS_FLY_MARK:
			fly_mark += val;
			break;
		default:
			break;
		}
	}
	void getAllProps(int& c, int& l, int& fm, int& p) {
		fm = fly_mark;
		p = point;
		c = coin;
		l = life;
	}

	static UserInfo* GetInstance();
};