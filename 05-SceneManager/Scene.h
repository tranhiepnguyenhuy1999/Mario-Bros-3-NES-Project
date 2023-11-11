#pragma once

#include "KeyEventHandler.h"

/*
*  Abstract class for a game scene
*/
class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

public: 
	CScene(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = NULL;
	}

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void getPlayerLevel(int& level) = 0;
	virtual void AddMovingObject(float x, float y, float nx = 0, float ny = 0, float ax = 0, float ay = 0, int ani_id = 0, int delete_times = 1000) = 0;
	virtual void AddStopMovingObjectAxisY(float x, float y, float nx = 0, float ny = 0, float ax = 0, float ay = 0, int ani_id = 0, int delete_times = 1000, bool direct = true) = 0;
	virtual void CreateNewObject(int id, float x, float y, float nx=0, float ny=0, LPGAMEOBJECT objSrc = NULL, int type=0)=0;
	virtual void playerTouchedButtonP() = 0;

};
typedef CScene * LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;