#include "TransportPile.h"

void CTransportPile::Render()
{
}

void CTransportPile::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PILE_BBOX_WIDTH / 2;
	t = y - PILE_BBOX_HEIGHT / 2;
	r = l + PILE_BBOX_WIDTH * 2;
	b = t + PILE_BBOX_HEIGHT*height;
}