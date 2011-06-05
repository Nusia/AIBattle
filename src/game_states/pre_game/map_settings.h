#pragma once

#include "i_pre_game.h"
#include "../../helpers/image_helper.h"
#include "../../helpers/text_handler.h"

class MapSettings : public IPreGame
{
public:
	MapSettings();
	void handle_input( SDL_Event* event );
	void update();
	void draw( SDL_Surface* screen );
	
private:
	TTF_Font* font;
};