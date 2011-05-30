#pragma once

#include "Math.h"

#include "game_states/game_state_manager.h"
#include "map/map.h"
#include "AI/a_star.h"

class AIBattle
{
public:
	AIBattle();
	void handle_event( SDL_Event *event );
	void update();
	void draw();

private:
	GameStateManager game_state_manager_;
	int win_width;
	int win_height;

	SDL_Surface* screen;
	const int SCREEN_BPP;
	const int FRAMES_PER_SECOND;

	void init_GL();
	void init();
};