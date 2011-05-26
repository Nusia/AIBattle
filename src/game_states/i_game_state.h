#pragma once

#include "SDL.h"

class IGameState
{
public:
	virtual void init() = 0;
	virtual void handle_input( SDL_Event* event ) = 0;
	virtual void update() = 0;
	virtual void draw( SDL_Surface* screen ) = 0;
	virtual bool isDone() = 0;
	virtual int get_next_state() = 0;
};

const enum{ PREGAME, INGAME };