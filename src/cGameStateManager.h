#pragma once

#include <vector>

#include "iGameState.h"
#include "cPreGameState.h"
#include "cInGameState.h"

class cGameStateManager
{
public:
	cGameStateManager();

	void Update();
	void Draw( SDL_Surface* screen );
	void HandleInput( SDL_Event* event );

private:
	iGameState* _pActiveState;
	std::vector<iGameState*> _vGameStates;
	cMouse* _pMouse;
};