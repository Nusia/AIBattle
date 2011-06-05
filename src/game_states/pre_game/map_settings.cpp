#include "map_settings.h"

MapSettings::MapSettings()
{
	font = TextHandler::get_font( "../resources/fonts/larabiefont_rg.ttf", 16 );
}

void MapSettings::handle_input( SDL_Event* event )
{
}

void MapSettings::update()
{
}

void MapSettings::draw( SDL_Surface* screen )
{
	TextHandler::render_text( 
		300, 300, font, 
		"MAP SETTINGS", 0, 200, 0, screen );
}