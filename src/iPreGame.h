#pragma once 

#include "SDL.h"

class iPreGame
{
public:
	virtual void HandleInput( SDL_Event* event ) = 0;
	virtual void Update() = 0;
	virtual void Draw( SDL_Surface* screen ) = 0;
};