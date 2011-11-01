#pragma once

#include "cPosition.h"
#include "SDL.h"

class cMouse
{
public:
	cMouse();
	void Update();
	void HandleEvent( SDL_Event* event );
	cPosition GetCurrentPos();
	cPosition GetPrevPos();
	cPosition DeltaPosFromLastUpdate();

private:
	cPosition _posCurrent;
	cPosition _posPrev;
};