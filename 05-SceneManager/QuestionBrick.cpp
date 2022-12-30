#include "QuestionBrick.h"

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->state== QUESTIONBRICK_STATE_TOUCHED)
	{
		animations->Get(ID_ANI_TOUCHED_QUESTION_BRICK)->Render(x, y);
	}
	else
	animations->Get(ID_ANI_UNTOUCHED_QUESTION_BRICK)->Render(x, y);

	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}
void CQuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);
}