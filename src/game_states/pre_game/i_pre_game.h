#pragma once 

#include "SDL.h"

class IPreGame
{
public:
	virtual void handle_input( SDL_Event* event ) = 0;
	virtual void update() = 0;
	virtual void draw( SDL_Surface* screen ) = 0;
};