
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PILE 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CPile : public CGameObject {
public:
	CPile(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};