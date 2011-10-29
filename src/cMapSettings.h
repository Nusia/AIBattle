#pragma once

#include <vector>
#include <fstream>

#include "iPreGame.h"
#include "cAStar.h"
#include "cMap.h"
#include "cPosition.h"
#include "cImageHelper.h"
#include "cTextHandler.h"

class cMapSettings : public iPreGame
{
public:
	//Functions
	//---------
	cMapSettings();
	void HandleInput( SDL_Event* event );
	void Update();
	void Draw( SDL_Surface* screen );
	
private:
	//Functions
	//---------
	
	//Variables
	//---------
	const Sint16 TILE_SIZE;
	float _fMapOffsetX;
	float _fMapOffsetY;
	
	cMap map_;
	std::vector< cPosition > _vPathList;
	
	TTF_Font* _pFont;
	SDL_Surface* _pWhiteTex;
	SDL_Surface* _pBlackTex;
	SDL_Surface* _pRedTex;
	SDL_Surface* _pGreenTex;
	SDL_Surface* _pBlueTex;
	
	//const enum tile_type{ WALKABLE, WALL, PLAYER01, PLAYER02 };
};