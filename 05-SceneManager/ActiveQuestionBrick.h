#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_ACTIVE_QUESTIONBRICK 10003

class CActiveQuestionBrick : public CGameObject {
public:
	CActiveQuestionBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};