#include "UserBoard.h"

void CUserBoard::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CUserBoard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}