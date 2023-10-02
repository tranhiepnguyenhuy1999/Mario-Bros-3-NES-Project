#pragma once

#include "Scene.h"

#define KEYEVENT_KEY_UP 1
#define KEYEVENT_KEY_DOWN 2
#define KEYEVENT_KEY_STATE 3



class CSampleKeyHandler: public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
