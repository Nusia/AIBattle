#pragma once

#include <vector>
#include <fstream>

#include "i_pre_game.h"
#include "../../AI/a_star.h"
#include "../../map/map.h"
#include "../../helpers/position.h"
#include "../../helpers/image_helper.h"
#include "../../helpers/text_handler.h"

class MapSettings : public IPreGame
{
public:
	//Functions
	//---------
	MapSettings();
	void handle_input( SDL_Event* event );
	void update();
	void draw( SDL_Surface* screen );
	
private:
	//Functions
	//---------
	
	//Variables
	//---------
	const int TILE_SIZE;
	float map_x_offset;
	float map_y_offset;
	
	Map map_;
	std::vector< Position > path_list_;
	
	TTF_Font* font;
	SDL_Surface* white_tex_;
	SDL_Surface* black_tex_;
	SDL_Surface* red_tex_;
	SDL_Surface* green_tex_;
	SDL_Surface* blue_tex_;
	
	//const enum tile_type{ WALKABLE, WALL, PLAYER01, PLAYER02 };
};