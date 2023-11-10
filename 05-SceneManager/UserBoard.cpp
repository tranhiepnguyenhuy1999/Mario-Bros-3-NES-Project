#include "UserBoard.h"

#include "Game.h"
#include "PlayScene.h"
#include "Camera.h"
#include "UserInfo.h"

#include "Mario.h"

#include "debug.h"
//8:6
CUserBoard* CUserBoard::__instance = NULL;
CUserBoard* CUserBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CUserBoard(0, 0);
	return __instance;
}
void CUserBoard::Render()
{
	translateNumberToSprite();

	int point, fly_mark, life, coin;
	UserInfo::GetInstance()->getAllProps(coin, life, fly_mark, point);
	
	int cHeight;
	float cx, cy;
	Camera::GetInstance()->getCamPosition(cx, cy);
	Camera::GetInstance()->getCamHeight(cHeight);

	x = cx + 80.0f;
	y = cy  + cHeight - 35/2;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BOARD)->Render(x, y);
	//coin
	for (int i = vcoin.size(); i >0; i--) {
		int aniId = getAniId(vcoin[i-1]);
		animations->Get(aniId)->Render(x - 78 + 134 + 4 + (vcoin.size()-i)*8, y - 18 + 8 + 6);
	}

	//life
	for (int i = vlife.size(); i > 0; i--) {
		int aniId = getAniId(vlife[i - 1]);
		animations->Get(aniId)->Render(x - 78 + 30 + 4 + (vlife.size() - i) * 8, y - 18 + 16 + 6);
	}

	// world point
	animations->Get(ID_ANI_NUMBER1)->Render(x - 78 +38 + 6, y -18 +8 + 6 );

	// time
	for (int i = 0; i < (int)vtime.size(); i++) {
		int aniId = getAniId(vtime[i]);
		animations->Get(aniId)->Render(x - 78 + 126 + 4 + i * 8, y - 18 + 16 + 6);
	}

	// point
	for (int i = 0; i < (int)vpoint.size(); i++) {
		int aniId = getAniId(vpoint[i]);
		animations->Get(aniId)->Render(x - 78 + 53 + 4 +i*8, y - 18 + 16 + 6);
	}

	//p 
	for (int i = 1; i < 7; i++) {
		if (i <= fly_mark) {
			animations->Get(ID_ANI_NUMBER_WHITE_LEFT)->Render(x - 78 + 53 + 4 + (i-1) * 8, y - 18 + 8 + 6);
		}
		else
			animations->Get(ID_ANI_NUMBER_BLACK_LEFT)->Render(x - 78 + 53 + 4 + (i-1) * 8, y - 18 + 8 + 6);
	}
	if (fly_mark ==6)
		animations->Get(ID_ANI_NUMBER_WHITE_P)->Render(x - 78 + 53 + 6 + 6 * 8 +2 , y - 18 + 8 + 6);
	else
		animations->Get(ID_ANI_NUMBER_BLACK_P)->Render(x - 78 + 53 + 6 + 6 * 8 + 2, y - 18 + 8 + 6);
}	
void CUserBoard::translateNumberToSprite() {
	vcoin.clear();
	vtime.clear();
	vlife.clear();
	vpoint.clear();

	int point, fly_mark, life, coin;
	UserInfo::GetInstance()->getAllProps(coin, life, fly_mark, point);

	//DebugOut(L"fly %d \n", isFlyStak);
	if (countdown >= 1 && loop_start != -1)
	{
		if (GetTickCount64() - loop_start > 1000)
		{

			loop_start = GetTickCount64();
			countdown--;
		}

	}
	int temp= this->countdown;
	//coin
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			vcoin.push_back(coin % 10);
		}else vcoin.push_back(coin / (10 ^ i));
	}
	//time
	for (int i = 2; i >=0; i--) {
		if (i == 0) {
			vtime.push_back(temp % 10);
		}
		else {
			int result = (int)(temp / pow(10, i));
			//DebugOut(L"i: %d \n", result);
			vtime.push_back(result);
			temp = temp - (int)(result * pow(10, i));
		}
	}
	// point
	for (int i = 6; i >= 0; i--) {
		if (i == 0) {
			vpoint.push_back((int)point % 10);
		}
		else {
			int result = (int)(point/pow(10, i));
			//DebugOut(L"i: %d \n", result);
			vpoint.push_back(result);
			point = point - (int)(result * pow(10, i));
		}
	}
	//life
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			vlife.push_back(life % 10);
		}
		else vlife.push_back((int)(life / pow(10, i)));
	}
	RenderBoundingBox();
}
int CUserBoard::getAniId(int num) {
	switch (num)
	{
	case 0:
		return ID_ANI_NUMBER0;
	case 1: 
		return ID_ANI_NUMBER1;
	case 2:
		return ID_ANI_NUMBER2;
	case 3:
		return ID_ANI_NUMBER3;
	case 4:
		return ID_ANI_NUMBER4;
	case 5:
		return ID_ANI_NUMBER5;
	case 6:
		return ID_ANI_NUMBER6;
	case 7:
		return ID_ANI_NUMBER7;
	case 8:
		return ID_ANI_NUMBER8;
	case 9:
		return ID_ANI_NUMBER9;
	default:
		return 0;
	}
}
void CUserBoard::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	int cWidth, cHeight;
	float l, t, r, b;
	float cx, cy;
	
	Camera::GetInstance()->getCamPosition(cx, cy);
	Camera::GetInstance()->getCamWidth(cWidth);
	Camera::GetInstance()->getCamHeight(cHeight);

	l = cx;
	t = cy + cHeight*0.75f - 35/2;
	r = l + cWidth;
	b = t + 35;

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;


	CGame::GetInstance()->Draw((float)cWidth/2, (float)cHeight - 35.0f/2, bbox, nullptr, 1.0f, rect.right - 1, rect.bottom - 1);
}
