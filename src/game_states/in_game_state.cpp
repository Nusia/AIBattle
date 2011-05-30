#include "in_game_state.h"

InGameState::InGameState()
{
}

void InGameState::init()
{
	std::cout << "Initiating ingame state.\n";
	map.init();
	std::cout << "Ingame state ready.\n";
}

void InGameState::handle_input( SDL_Event* event )
{
	AStar a_star( map.get_map(), map.get_players_pos() );
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		Position cell_pos;
		cell_pos.x = (int)floorf(
			( (event->motion.x + map.getcam_pos_().x) / 
			( (float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );

		cell_pos.y = (int)floorf( 
			((event->motion.y + map.getcam_pos_().y) / 
			((float)(MAP_ROWS*TILE_HEIGHT*0.75) / MAP_ROWS) ) );

		if( map.is_pos_walkable( cell_pos ) )
		{
			tmp_list_.clear();
			tmp_list_ = a_star.get_best_path( cell_pos, map.getplayer_01_pos_() );
			tmp_list_.push_back( cell_pos );
		}
	}
	map.handle_event( event );
}

void InGameState::update()
{
	if( !tmp_list_.empty() )
	{
		map.setplayer_01_pos_( tmp_list_.front() );
		tmp_list_.erase( tmp_list_.begin() );
	}
}

void InGameState::draw( SDL_Surface* screen )
{
	map.draw( screen );
}

bool InGameState::isDone()
{
	return false;
}

int InGameState::get_next_state()
{
	return PREGAME;
}
