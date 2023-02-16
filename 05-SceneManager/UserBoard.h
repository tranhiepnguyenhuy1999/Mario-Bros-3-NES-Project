#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

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
public:
	CUserBoard(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};