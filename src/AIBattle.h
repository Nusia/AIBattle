#pragma once

#include "Math.h"

#include "game_states/game_state_manager.h"
#include "map/map.h"
#include "AI/a_star.h"

class AIBattle
{
private:

	GameStateManager _game_state_manager;
	int win_width;
	int win_height;

	SDL_Surface* screen;
	const int SCREEN_BPP;
	const int FRAMES_PER_SECOND;

	void init_GL();
	void init();

public:
	AIBattle();
	void handle_event( SDL_Event *event );
	void update();
	void draw();
};