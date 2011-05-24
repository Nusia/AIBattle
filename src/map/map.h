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
	//Variables
	//---------
	std::vector< std::vector<int> > _map;
	Position _unit_pos;
	Position _cam_pos;

	SDL_Surface* character_basic;
	SDL_Surface* stone_tile_low;
	SDL_Surface* stone_tile_high;
	SDL_Surface* shadow_north_east;
	SDL_Surface* shadow_east;
	SDL_Surface* shadow_south_east;
	SDL_Surface* shadow_south;
	SDL_Surface* shadow_south_west;
	SDL_Surface* shadow_west;
	SDL_Surface* shadow_north_west;
	SDL_Surface* shadow_north;

	//Functions
	//---------
	SDL_Surface* load_image(char *file);

public:
	static const enum tile_type{ WALKABLE, WALL, UNIT };

	Map();
	void update();
	void draw( SDL_Surface* screen );

	bool is_pos_walkable( Position pos );

	//Set & Get
	void 
		set_unit_pos( Position unit_pos ) { _unit_pos = unit_pos; }

	std::vector<std::vector<int>> 
		get_map() const { return _map; }

	Position 
		get_cam_pos() { return _cam_pos; }

	//TMP
	void handle_event( SDL_Event *event );
};