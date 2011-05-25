#pragma once

#define MAP_COLS 60
#define MAP_ROWS 40
#define TILE_WIDTH 15
#define TILE_HEIGHT 15

#include <iostream>
#include <fstream>
#include <vector>
#include "SDL.h"
#include "SDL_opengl.h"
#include "position.h"

class Map
{
private:
	std::vector< std::vector<int> > _map;
	Position _player_01_pos;
	Position _player_02_pos;

public:
	Map();
	void draw() const;

	void toggle_active_cell( int type, Position pos );

	std::vector<std::vector<int>> get_map() const { return _map; }

	void save_map();
	void load_map();
	void reset_map();

	static enum Tile_type{ WALKABLE, WALL, PLAYER01, PLAYER02 };
	std::string tile_type_name[4];
};
