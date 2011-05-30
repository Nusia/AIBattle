#pragma once

#include <vector>

#include "i_game_state.h"
#include "pre_game_state.h"
#include "in_game_state.h"

class GameStateManager
{
public:
	GameStateManager();

	void update();
	void draw( SDL_Surface* screen );
	void handle_input( SDL_Event* event );

private:
	IGameState* active_state_;
	std::vector<IGameState*> game_states_;
};