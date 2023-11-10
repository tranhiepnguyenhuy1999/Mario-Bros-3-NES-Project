#include "TileMap.h"
#include "debug.h"
#include "Camera.h"

CTileMap* CTileMap::__instance = NULL;

void CTileMap::Render()
{

	float cx, cy;

	Camera* cam = Camera::GetInstance();
	cam->getCamPosition(cx, cy);

	CAnimations* animations = CAnimations::GetInstance();

	int max_rows = tileMap.size();

	//DebugOut(L"chekc %d", lengthY);

	for (int i = 0; i < max_rows; i++)
	{
		for (float j = 0; j < tileMap[i].size(); j++)
		{
			// check tile x y 
			float l, t, r, b;
			l = (float)(j * 16);
			t = (float)(i * 16);
			r = (float)(l + 16);
			b = (float)(t + 16);

			if (cam->isCamContain(l, t, r, b))
			{
				animations->Get(stoi(tileMap[i][j]))->Render(l, t);
			}
		}
	}
}

CTileMap* CTileMap::GetInstance()
{
	if (__instance == NULL) __instance = new CTileMap(0,0);
	return __instance;
}