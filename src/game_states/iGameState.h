#pragma once

#include "SDL.h"

class iGameState
{
public:
	virtual void Init() = 0;
	virtual void HandleInput( SDL_Event* event ) = 0;
	virtual void Update() = 0;
	virtual void Draw( SDL_Surface* screen ) = 0;
	virtual bool IsDone() = 0;
	virtual int GetNextState() = 0;
};

const enum{ PREGAME, INGAME };