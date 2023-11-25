#include "TransportPile.h"
#include "Pile.h"

void CTransportPile::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (type == 1)
	{
	for (int i = 0; i < height; i++) {
		animations->Get(ID_ANI_PILE_HEAD_FIRST)->Render(x, y);
		animations->Get(ID_ANI_PILE_HEAD_LAST)->Render(x + 16, y);
		animations->Get(ID_ANI_PILE_BODY_FIRST)->Render(x, y + 16 + i * 16);
		animations->Get(ID_ANI_PILE_BODY_LAST)->Render(x + 16, y + 16 + i * 16);
	}
	}
	else
	{
		animations->Get(98)->Render(x, y);
		animations->Get(99)->Render(x + 16, y);
		for (int i = 0; i < height; i++) {
			animations->Get(103)->Render(x, y + 16 + i * 16);
			animations->Get(104)->Render(x + 16, y + 16 + i * 16);
		}
	}

}

void CTransportPile::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PILE_BBOX_WIDTH / 2;
	t = y - PILE_BBOX_HEIGHT / 2;
	r = l + PILE_BBOX_WIDTH * 2;
	b = t + PILE_BBOX_HEIGHT*(height + 1);
}