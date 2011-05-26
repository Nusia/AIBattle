#pragma once

#include <vector>

#include "i_game_state.h"
#include "pre_game_state.h"
#include "in_game_state.h"

class GameStateManager
{
private:
	IGameState* _active_state;
	std::vector<IGameState*> _game_states;

public:
	GameStateManager();

	void update();
	void draw( SDL_Surface* screen );
	void handle_input( SDL_Event* event );
};