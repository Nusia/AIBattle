#pragma once

#define MAP_COLS 60
#define MAP_ROWS 40
#define TILE_WIDTH 64
#define TILE_HEIGHT 64

#include <iostream>
#include <fstream>
#include <vector>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include "cPosition.h"
#include "cImageHelper.h"

class cMap
{
public:
	static const enum tile_type{ WALKABLE, WALL, PLAYER01, PLAYER02 };

	cMap();
	void Init();
	void Update();
	void Draw( SDL_Surface* screen );

	bool IsPosWalkable( cPosition pos );

	//Set & Get
	void 
		SetPlayer01Pos( cPosition unit_pos ) { _player01Pos = unit_pos; }

	cPosition cMap::GetPlayer01Pos() { return _player01Pos; }

	std::vector<cPosition> cMap::GetPlayersPos();

	std::vector<std::vector<int>> 
		GetMap() const { return _vMap; }

	//TMP
	void HandleEvent( SDL_Event *event );


private:
	//Variables
	//---------
	std::vector< std::vector<int> > _vMap;

	cPosition _player01Pos;
	cPosition _player02Pos;

	//Functions
	//---------
	void _loadMap();
	void _resetMap();
};