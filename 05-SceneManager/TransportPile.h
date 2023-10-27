#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define PILE_BBOX_WIDTH 16
#define PILE_BBOX_HEIGHT 16

class CTransportPile : public CGameObject {
	float height;	
public:
	CTransportPile(float x, float y, float height) : CGameObject(x, y) {
		this->height = height;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};