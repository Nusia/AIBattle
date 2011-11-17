#pragma once 

#include <irrlicht.h>
#include "SDL.h"

class iPreGame
{
public:
	virtual void HandleInput( SDL_Event* event ) = 0;
	virtual void Update( irr::IrrlichtDevice* device ) = 0;
	virtual void Draw( irr::IrrlichtDevice* device ) = 0;
};