#include "UserBoard.h"
//8:6
void CUserBoard::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BOARD)->Render(x, y);
	//coin 
	animations->Get(ID_ANI_NUMBER1)->Render(x - 78 + 134 + 4, y - 18 + 8 + 6);
	animations->Get(ID_ANI_NUMBER1)->Render(x - 78 + 134 + 4 + 8, y - 18 + 8 + 6);

	//life
	animations->Get(ID_ANI_NUMBER1)->Render(x - 78 + 30 + 4, y - 18 + 16 + 6);
	animations->Get(ID_ANI_NUMBER1)->Render(x - 78 + 30 + 4 + 8, y - 18 + 16 + 6);

	// world point
	animations->Get(ID_ANI_NUMBER1)->Render(x - 78 +38 + 6, y -18 +8 + 6 );

	// time
	animations->Get(ID_ANI_NUMBER0)->Render(x - 78 + 126 + 4, y - 18 + 16 + 6);
	animations->Get(ID_ANI_NUMBER0)->Render(x - 78 + 126 + 4 +	8, y - 18 + 16 + 6);
	animations->Get(ID_ANI_NUMBER0)->Render(x - 78 + 126 + 4 + 8*2, y - 18 + 16 + 6);

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