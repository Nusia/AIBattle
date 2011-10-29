#pragma once

#include "Math.h"

#include "game_states/cGameStateManager.h"
#include "map/cMap.h"
#include "AI/cAStar.h"

class cAIBattle
{
public:
	cAIBattle();
	void HandleEvent( SDL_Event *event );
	void Update();
	void Draw();

private:
	cGameStateManager _GameStateManager;
	int _nWinWidth;
	int _nWinHeight;

	SDL_Surface* _pScreen;
	const int SCREEN_BPP;
	const int FRAMES_PER_SECOND;

	void _initGL();
	void _init();
};