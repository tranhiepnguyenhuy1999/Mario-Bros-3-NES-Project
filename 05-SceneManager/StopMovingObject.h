#pragma once
#include "MovingObject.h"

class CStopMovingObjectAxisY: public CMovingObject
{
	bool direction; // direction moving from the start

	ULONGLONG count_start;

public:

	CStopMovingObjectAxisY(float x, float y, float vx, float ax, float ay, float vy, int ani_id, int delete_times, bool direct = true) : CMovingObject(x,  y,  vx,  ax,  ay,  vy,  ani_id, delete_times) {
		this->direction = direct;
		count_start = -1;
	};


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		
		if (direction) {
			if (vy < 0)
			{
				vy = 0;
				count_start = GetTickCount64();
			}
		}
		else if (vy > 0)
		{
			vy = 0;
			count_start = GetTickCount64();
		}
		
		if (vy == 0)
		{
			if(GetTickCount64() - count_start > 100) this->Delete();
		}
		else CMovingObject::Update(dt, coObjects);
	};

};

