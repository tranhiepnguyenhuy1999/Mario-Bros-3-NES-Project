#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CTileMap : public CGameObject {
	static CTileMap* __instance;
	
	vector<vector<string>> tileMap;

public:
	CTileMap(float x, float y) : CGameObject(x, y) {};
	void createTileMap(vector<vector<string>> content) {
		tileMap = content;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b){};

	static CTileMap* GetInstance();
};