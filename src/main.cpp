#pragma once

#include <iostream>

#include "SDL.h"

#include "AIBattle.h"

AIBattle *_AIBattle;

int main( int argc, char* args[] )
{
	_AIBattle = new AIBattle();

	SDL_Event event;
	bool quit = false;

	while( !quit )
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
				quit = true;
			else
				_AIBattle->handle_events( &event );

		}
		_AIBattle->draw();
	}

	//Quit SDL
    SDL_Quit();

    return 0;
}