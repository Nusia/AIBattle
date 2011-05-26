#include "game_state_manager.h"

GameStateManager::GameStateManager()
{
	_game_states.push_back( new PreGameState() );
	_game_states.push_back( new InGameState() );
	_active_state = _game_states[0];
	_active_state->init();
}

void GameStateManager::update()
{
	_active_state->update();
	if( _active_state->isDone() )
	{
		_active_state = _game_states[_active_state->get_next_state()];
		_active_state->init();
	}
}

void GameStateManager::draw( SDL_Surface* screen )
{
	_active_state->draw( screen );
}

void GameStateManager::handle_input( SDL_Event* event )
{
	_active_state->handle_input( event );
}