#include "Layer.h"
#include "Camera.h"
#include "Textures.h"

CLayer* CLayer::__instance = NULL;

CLayer* CLayer::GetInstance()
{
	if (__instance == NULL) __instance = new CLayer(0, 0);
	return __instance;
}

void CLayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive)
	{
		if (GetTickCount64() - count_start > LAYER_COUNT_TIMEOUT)
			{
				count_start = GetTickCount64();

				if (state == LAYER_STATE_FADING_FROM_0_TO_1)
				{
					alpha += 0.1f;
					if (alpha > 1)
					{
						alpha = 1;
						isActive = false;
						count_start = GetTickCount64();
					}
		
				}
				else
				{
					alpha -= 0.1f;
					if (alpha < 0)
					{
						alpha = 0;
						isActive = false;
					}
				}

			}
	}
	else
	{
		if (GetTickCount64() - count_start > 500) alpha = 0.0f;

	}
	CGameObject::Update(dt, coObjects);
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

	CGame::GetInstance()->Draw(cw/2, ch/2, bbox, &rect, alpha);
}

void CLayer::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}
void CLayer::SetState(int state)
{
	switch (state) {
	case LAYER_STATE_FADING_FROM_0_TO_1:
		count_start = GetTickCount64();
		break;
	case LAYER_STATE_FADING_FROM_1_TO_0:
		count_start = GetTickCount64();
		break;
	}

	CGameObject::SetState(state);
}