#include "pre_game_state.h"

void PreGameState::init()
{
	_done = false;
	font = TextHandler::get_font( "../resources/fonts/larabiefont_rg.ttf", 16 );
}

void PreGameState::handle_input( SDL_Event* event )
{
	if( event->key.keysym.sym == SDLK_SPACE )
		_done = true;
}

void PreGameState::update()
{
}

void PreGameState::draw( SDL_Surface* screen )
{
	TextHandler::render_text( 
		300, 200, 
		font,
		"Press space to start game.", 
		0, 200, 0, 
		screen );
}

bool PreGameState::isDone()
{
	return _done;
}

int PreGameState::get_next_state()
{
	return INGAME;
}
