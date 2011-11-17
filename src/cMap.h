#pragma once

#define MAP_COLS 60
#define MAP_ROWS 40
#define TILE_WIDTH 64.0f
#define TILE_HEIGHT 64.0f

#include <irrlicht.h>
#include <iostream>
#include <fstream>
#include <vector>


using namespace irr;

class cMap
{
public:
	static const enum tile_type{ WALKABLE, WALL, PLAYER01, PLAYER02 };

	cMap();
	void Init();
	void Update();
	void Draw( irr::IrrlichtDevice* device );

	bool IsPosWalkable( irr::core::vector2d<irr::s32> pos );

	//Set & Get
	void 
		SetPlayer01Pos( irr::core::vector2d<irr::s32> unit_pos ) { _player01Pos = unit_pos; }

	irr::core::vector2d<irr::s32> cMap::GetPlayer01Pos() { return _player01Pos; }

	std::vector<irr::core::vector2d<irr::s32>> cMap::GetPlayersPos();

	std::vector<std::vector<int>> 
		GetMap() const { return _vMap; }

private:
	//Variables
	//---------
	std::vector< std::vector<int> > _vMap;

	irr::core::vector2d<irr::s32> _player01Pos;
	irr::core::vector2d<irr::s32> _player02Pos;

	//Functions
	//---------
	void _loadMap();
	void _resetMap();
};