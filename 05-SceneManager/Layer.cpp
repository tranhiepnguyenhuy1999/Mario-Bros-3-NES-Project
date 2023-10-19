#include "Layer.h"
#include "Camera.h"
#include "Textures.h"

CLayer* CLayer::__instance = NULL;
CLayer* CLayer::GetInstance()
{
	if (__instance == NULL) __instance = new CLayer(0, 0);
	return __instance;
}
void CLayer::Render()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	Camera::GetInstance()->getCamBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	int cw, ch;
	Camera::GetInstance()->getCamWidth(cw);
	Camera::GetInstance()->getCamHeight(ch);

	CGame::GetInstance()->Draw(cw/2, ch/2, bbox, &rect, BBOX_ALPHA);
}

void CLayer::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}