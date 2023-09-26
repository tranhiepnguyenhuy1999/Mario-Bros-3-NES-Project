#pragma once

using namespace std;
#include "GameObject.h"
#include <Windows.h>

#define MAX_MAP_WIDTH 3328
#define MAX_MAP_HEIGHT 464

class Camera
{
	static Camera* __instance;

	float l, t, r, b;

	int cWidth;
	int cHeight;

	float px; // player x
	float py; // player y

	boolean isFixed;

public:
	Camera() {
		l = 0; t = 256.f; r = 0; b = 0;
		cWidth = 0;
		cHeight = 0;
		px = 0; py = 0;
	}

	void setCamWidth(int width) { cWidth = width; r = l + cWidth; };
	void setCamHeight(int height) { cHeight = height; b = t + cHeight; };


	void getCamWidth(int& width) { width = cWidth; };
	void getCamHeight(int& height) { height = cHeight; };

	void getPlayerPosition(float& x, float& y) { x = px; y = py; };

	void getCamBoundingBox(float& cl, float& ct, float& cr, float& cb) { cl = l; ct = t; cr = r; cb = b; };
	
	void setInitialCamProps(float cl, float ct, boolean isCameraFixed) {
		l = cl;
		r = l + cWidth;
		t = ct;
		b = t + cHeight;
		isFixed = isCameraFixed;
	}

	void setCamPosition(float px, float py) {
	
		this->px = px;
		this->py = py;

		if (isFixed) return;

		l = px - cWidth/2;
		r = l + cWidth;
		if (py < t + cHeight / 4)
		{
			t = py - cHeight/4;
			b = t + cHeight;
		}
		else if (py > t + cHeight / 2) {
			t = py - cHeight / 2;
			b = t + cHeight;
		}

		if (l < 0) { l = 0; r = l + cWidth; }
		else if (r > MAX_MAP_WIDTH) { r = MAX_MAP_WIDTH; l = r - cWidth; }

		if (t < 0) { t = 0; b = t + cHeight; }
		else if (b > MAX_MAP_HEIGHT) { b = MAX_MAP_HEIGHT; t = b - cHeight; }
	}
	void getCamPosition(float& cx, float& cy) {
		cx = l;
		cy = t;
	}
	bool isCamContain(float objl, float objt, float objr, float objb) {
		return !(objr < l || objl > r || objt > b || objb < t);
	}
	bool isCamContainObject(LPGAMEOBJECT obj) {
		float o_l, o_t, o_r , o_b;
		obj->GetBoundingBox(o_l, o_t, o_r, o_b);
		return !(o_r < l || o_l > r || o_t > b || o_b < t);
	}
	void checkIsCameraOver(vector<LPGAMEOBJECT>& objects) {
		//for (size_t i = 0; i < objects.size(); i++)
		//{
		//	float objl, objt, objr, objb;
		//	objects[i]->GetBoundingBox(objl, objt, objr, objb);
		//	if (isCamContain(objl, objt, objr, objb))
		//	{
		//		objects[i]->setIsActiveTrue();
		//	}
		//	if (dynamic_cast<CGunShip*>(objects[i])) continue;
		//	else if (objr < l || objt < b) {
		//		objects[i]->setIsCameraOverTrue();
		//	}
		//}
	}

	static Camera* GetInstance();
};