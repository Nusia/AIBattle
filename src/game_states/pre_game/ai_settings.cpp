#include "ai_settings.h"

AISettings::AISettings()
{
	font = TextHandler::get_font( "../resources/fonts/larabiefont_rg.ttf", 16 );
}

void AISettings::handle_input( SDL_Event* event )
{
}

void AISettings::update()
{
}

void AISettings::draw( SDL_Surface* screen )
{
	TextHandler::render_text( 
		300, 300, font, 
		"AI SETTINGS", 0, 200, 0, screen );
}