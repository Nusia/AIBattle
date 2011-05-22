#pragma once

#define MAP_COLS 80
#define MAP_ROWS 60
#define TILE_WIDTH 10
#define TILE_HEIGHT 10

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_opengl.h"

class Map
{
private:
	enum{ WALKABLE, WALL, UNIT };
	std::vector< std::vector<int> > _map;

public:
	Map();
	void draw() const;

	void toggle_active_cell( int x, int y );

	std::vector<std::vector<int>> get_map() const { return _map; }
};