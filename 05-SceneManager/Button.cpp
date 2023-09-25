#include "Button.h"

void CButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(state==BUTTON_STATE_ACTIVE)
		animations->Get(ID_ANI_BUTTON_ACTIVE)->Render(x, y);
	else
	{
		animations->Get(ID_ANI_BUTTON)->Render(x, y);

	}
	//RenderBoundingBox();
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BUTTON_BBOX_WIDTH / 2;
	t = y - BUTTON_BBOX_HEIGHT / 2;
	r = l + BUTTON_BBOX_WIDTH;
	b = t + BUTTON_BBOX_HEIGHT;
}