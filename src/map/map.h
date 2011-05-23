#pragma once

#define MAP_COLS 80
#define MAP_ROWS 60
#define TILE_WIDTH 10
#define TILE_HEIGHT 10

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_opengl.h"
#include "../helpers/position.h"

class Map
{
private:
	std::vector< std::vector<int> > _map;
	std::vector< Position > _path;

public:
	static const enum tile_type{ WALKABLE, WALL, UNIT };

	Map();
	void draw() const;

	void toggle_active_cell( int x, int y );
	void set_path( std::vector< Position > path ) { _path = path; }

	std::vector<std::vector<int>> get_map() const { return _map; }
};