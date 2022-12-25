#include "Portal.h"
#define ID_ANI_BRICK 10003

class CDoorPoral: public CPortal
{
	void Render();
public:
	CDoorPoral(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox(void);

	int GetSceneId();
	int IsBlocking();
};

