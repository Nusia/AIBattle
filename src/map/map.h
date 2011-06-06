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

#include "../helpers/position.h"
#include "../helpers/image_helper.h"

class Map
{
public:
	static const enum tile_type{ WALKABLE, WALL, PLAYER01, PLAYER02 };

	Map();
	void init();
	void update();
	void draw( SDL_Surface* screen );

	bool is_pos_walkable( Position pos );

	//Set & Get
	void 
		setplayer_01_pos_( Position unit_pos ) { player_01_pos_ = unit_pos; }

	Position Map::getplayer_01_pos_() { return player_01_pos_; }

	std::vector<Position> Map::get_players_pos();

	std::vector<std::vector<int>> 
		get_map() const { return map_; }

	//TMP
	void handle_event( SDL_Event *event );


private:
	//Variables
	//---------
	std::vector< std::vector<int> > map_;

	Position player_01_pos_;
	Position player_02_pos_;

	//Functions
	//---------
	void load_map();
	void reset_map();
};