#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Map.h"
#include "CloudBrick.h"
#include "TileSet.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
#include "UserBoard.h"
#include "DownBrick.h"
#include <sstream>
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	
	void _ParseSection_TILEDMAP(string line);
	void _ParseSection_TILESET(string line);
	
	void _ParseSection_CAMERA(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public:

	CPlayScene(int id, LPCWSTR filePath);
	
	virtual void createNewObject(int id, float x, float y, float nx, float ny, LPGAMEOBJECT objSrc = NULL);
	virtual void playerTouchedButtonP();

	virtual void AddMovingObject(float x, float y, float nx, float ny, float ax, float ay, int ani_id, int delete_times);
	virtual void AddStopMovingObjectAxisY(float x, float y, float nx, float ny, float ax, float ay, int ani_id, int delete_times, bool direct);

	
	virtual void getPlayerLevel(int& level) {
		player->getLevel(level);
	};

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

