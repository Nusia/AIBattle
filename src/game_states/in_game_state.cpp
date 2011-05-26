#include "in_game_state.h"

InGameState::InGameState()
{
}

void InGameState::init()
{
}

void InGameState::handle_input( SDL_Event* event )
{
	AStar a_star( map.get_map(), map.get_players_pos() );
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		Position cell_pos;
		cell_pos.x = (int)floorf(
			( (event->motion.x + map.get_cam_pos().x) / 
			( (float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );

		cell_pos.y = (int)floorf( 
			((event->motion.y + map.get_cam_pos().y) / 
			((float)(MAP_ROWS*TILE_HEIGHT*0.75) / MAP_ROWS) ) );

		if( map.is_pos_walkable( cell_pos ) )
		{
			_tmp_list.clear();
			_tmp_list = a_star.get_best_path( cell_pos, map.get_player_01_pos() );
			_tmp_list.push_back( cell_pos );
		}
	}
	map.handle_event( event );
}

void InGameState::update()
{
	if( !_tmp_list.empty() )
	{
		map.set_player_01_pos( _tmp_list.front() );
		_tmp_list.erase( _tmp_list.begin() );
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
