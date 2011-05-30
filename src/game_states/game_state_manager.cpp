#include "game_state_manager.h"

GameStateManager::GameStateManager()
{
	game_states_.push_back( new PreGameState() );
	game_states_.push_back( new InGameState() );
	active_state_ = game_states_[0];
	active_state_->init();
}

void GameStateManager::update()
{
	active_state_->update();
	if( active_state_->isDone() )
	{
		active_state_ = game_states_[active_state_->get_next_state()];
		active_state_->init();
	}
}

void GameStateManager::draw( SDL_Surface* screen )
{
	active_state_->draw( screen );
}

void GameStateManager::handle_input( SDL_Event* event )
{
	active_state_->handle_input( event );
}