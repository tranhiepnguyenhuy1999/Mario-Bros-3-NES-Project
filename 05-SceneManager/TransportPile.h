#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define PILE_BBOX_WIDTH 16
#define PILE_BBOX_HEIGHT 16

class CTransportPile : public CGameObject {
	int height;	
	int type;
public:
	CTransportPile(float x, float y, int height, int obj_type) : CGameObject(x, y) {
		this->height = height;
		type = obj_type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};