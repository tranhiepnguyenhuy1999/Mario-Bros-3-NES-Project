#include "UserBoard.h"
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
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BOARD)->Render(x, y);
	//coin
	for (int i = coinA.size(); i >0; i--) {
		int aniId = getAniId(coinA[i-1]);
		animations->Get(aniId)->Render(x - 78 + 134 + 4 + (coinA.size()-i)*8, y - 18 + 8 + 6);
	}

	//life
	for (int i = lifeA.size(); i > 0; i--) {
		int aniId = getAniId(lifeA[i - 1]);
		animations->Get(aniId)->Render(x - 78 + 30 + 4 + (lifeA.size() - i) * 8, y - 18 + 16 + 6);
	}

	// world point
	animations->Get(ID_ANI_NUMBER1)->Render(x - 78 +38 + 6, y -18 +8 + 6 );

	// time
	for (int i = 0; i < timeA.size(); i++) {
		int aniId = getAniId(timeA[i]);
		animations->Get(aniId)->Render(x - 78 + 126 + 4 + i * 8, y - 18 + 16 + 6);
	}

	// point
	for (int i = 0; i < 7; i++) {
		animations->Get(ID_ANI_NUMBER0)->Render(x - 78 + 53 + 4 +i*8, y - 18 + 16 + 6);
	}

	//p 
	for (int i = 0; i < 6; i++) {
		animations->Get(ID_ANI_NUMBERLEFT)->Render(x - 78 + 53 + 4 + i * 8, y - 18 + 8 + 6);
	}
	animations->Get(ID_ANI_NUMBERP)->Render(x - 78 + 53 + 6 + 6 * 8 +2 , y - 18 + 8 + 6);
}	

void CUserBoard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
void CUserBoard::translateNumberToSprite() {
	int point, coin, life;
	CGame::GetInstance()->GetCurrentScene()->getPlayerProps(coin, point, life);
	coinA.clear();
	timeA.clear();
	lifeA.clear();
	pointA.clear();
	int tempTime;
	CountdownTimer::GetInstance()->getCounter(tempTime);
	//coin
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			coinA.push_back(coin % 10);
		}else coinA.push_back(coin / (10 ^ i));
	}
	//time
	for (int i = 2; i >=0; i--) {
		if (i == 0) {
			timeA.push_back(tempTime % 10);
		}
		else {
		timeA.push_back(tempTime / pow(10,i));
		tempTime = tempTime - (tempTime / (pow(10, i))) * pow(10, i);
		}
	}
	//life
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			lifeA.push_back(life % 10);
		}
		else lifeA.push_back(life / pow(10, i));
	}
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