
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PILE_HEAD_FIRST 7
#define ID_ANI_PILE_HEAD_LAST 8
#define ID_ANI_PILE_BODY_FIRST 10
#define ID_ANI_PILE_BODY_LAST 11

#define PILE_WIDTH 32

#define PILE_BBOX_WIDTH 16
#define PILE_BBOX_HEIGHT 16

class CPile : public CGameObject {
	float height;
public:
	CPile(float x, float y, float height) : CGameObject(x, y) {
		this->height = height;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};