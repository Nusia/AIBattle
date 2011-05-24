#pragma once

#define MAP_COLS 100
#define MAP_ROWS 80
#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define COLORKEY 255, 0, 255 //Your Transparent colour

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include "../helpers/position.h"

class Map
{
private:
	std::vector< std::vector<int> > _map;
	std::vector< Position > _path;
	Position _unit_pos;
	Position _cam_pos;

	GLuint texture;
	GLenum texture_format;

	SDL_Surface* character_basic;
	SDL_Surface* stone_tile_low;
	SDL_Surface* stone_tile_high;

public:
	static const enum tile_type{ WALKABLE, WALL, UNIT };

	Map();
	void draw( SDL_Surface* screen );

	void toggle_active_cell( int x, int y );

	SDL_Surface* load_image(char *file);

	bool is_pos_walkable( Position pos );

	void set_path( std::vector< Position > path ) { _path = path; }

	void set_unit_pos( Position unit_pos ) { _unit_pos = unit_pos; }

	std::vector<std::vector<int>> get_map() const { return _map; }

	Position get_cam_pos() { return _cam_pos; }

	//TMP
	void handle_event( SDL_Event *event );
};