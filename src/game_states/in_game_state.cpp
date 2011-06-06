#include "in_game_state.h"

InGameState::InGameState()
{
}

void InGameState::init()
{
	std::cout << "Initiating ingame state.\n";
	map.init();
	
	cam_pos_ = Position(0, 0);
		
	character_player_01 = ImageHelper::load_image("../resources/character_basic_green.png");
	character_player_02 = ImageHelper::load_image("../resources/character_basic_red.png");
	stone_tile_low = ImageHelper::load_image("../resources/stone_tile_low_64.png");
	stone_tile_high = ImageHelper::load_image("../resources/stone_tile_high_64.png");

	shadow_north_east = ImageHelper::load_image("../resources/shadow_north_east.png");
	shadow_east = ImageHelper::load_image("../resources/shadow_east.png");
	shadow_south_east = ImageHelper::load_image("../resources/shadow_south_east.png");	
	shadow_south = ImageHelper::load_image("../resources/shadow_south.png");
	shadow_south_west = ImageHelper::load_image("../resources/shadow_south_west.png");
	shadow_west = ImageHelper::load_image("../resources/shadow_west.png");
	shadow_north_west = ImageHelper::load_image("../resources/shadow_north_west.png");
	shadow_north = ImageHelper::load_image("../resources/shadow_north.png");
	
	std::cout << "Ingame state ready.\n";
}

void InGameState::handle_input( SDL_Event* event )
{
	if( event->type == SDL_KEYDOWN )
	{
		if( event->key.keysym.sym == SDLK_DOWN )
			cam_pos_.y += 25;
		if( event->key.keysym.sym == SDLK_UP && cam_pos_.y > 0 )
			cam_pos_.y -= 25;
		if( event->key.keysym.sym == SDLK_RIGHT )
			cam_pos_.x += 25;
		if( event->key.keysym.sym == SDLK_LEFT && cam_pos_.x > 0)
			cam_pos_.x -= 25;
	}
	
	AStar a_star( map.get_map(), map.get_players_pos() );
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		Position cell_pos;
		cell_pos.x = (int)floorf(
			( (event->motion.x + cam_pos_.x) / 
			( (float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );

		cell_pos.y = (int)floorf( 
			((event->motion.y + cam_pos_.y) / 
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
	SDL_Rect srect, drect;
	srect.x = 0;
	srect.y = 0;
	srect.w = 64;
	drect.w = TILE_WIDTH;
	std::vector< std::vector< int >> map_ = map.get_map();

	for( int col = 0; col < MAP_COLS; ++col )
	{
		for( int row = 0; row < MAP_ROWS; ++row )
		{
			srect.h = 64;
			drect.h = TILE_HEIGHT;
			drect.x = col * TILE_WIDTH - cam_pos_.x; 
			drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - cam_pos_.y);

			switch( map_[col][row] )
			{
			case map.WALL: 
				srect.h = 128;
				drect.h = TILE_HEIGHT*2;
				drect.y -= TILE_HEIGHT;
				SDL_BlitSurface( stone_tile_high, &srect, screen, &drect );

				if( col > 0 && row > 0 &&
					map_[col-1][row] != map.WALL && 
					map_[col][row-1] != map.WALL )
				{
					drect.x = (col-1) * TILE_WIDTH - cam_pos_.x;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - cam_pos_.y);
					SDL_BlitSurface( shadow_south_east, &srect, screen, &drect );
				}
				if( col > 0 &&
					map_[col-1][row] != map.WALL )
				{
					srect.h = TILE_HEIGHT*1.35;
					drect.h = TILE_HEIGHT*1.35;
					drect.x = (col-1) * TILE_WIDTH - cam_pos_.x;
					drect.y = (Sint16)((row-1)*TILE_HEIGHT*0.75 - cam_pos_.y) - 2;
					SDL_BlitSurface( shadow_east, &srect, screen, &drect );
				}
				if( row > 0 &&
					map_[col][row-1] != map.WALL )
				{
					drect.x = (col) * TILE_WIDTH - cam_pos_.x;
					drect.y = (Sint16)((row-2) * TILE_HEIGHT * 0.75 - cam_pos_.y) - TILE_HEIGHT*0.15;
					SDL_BlitSurface( shadow_south, &srect, screen, &drect );
				}
				if( col > 0 && row < MAP_ROWS-1 &&
					map_[col-1][row+1] != map.WALL && 
					map_[col][row+1] != map.WALL &&
					map_[col-1][row] != map.WALL)
				{
					drect.x = (col-1) * TILE_WIDTH - cam_pos_.x;
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - cam_pos_.y) -2;
					SDL_BlitSurface( shadow_north_east, &srect, screen, &drect );
				}
				break;

			case map.WALKABLE:
				drect.h = TILE_HEIGHT;
				drect.y -= (Sint16)(TILE_HEIGHT * 0.25);
				SDL_BlitSurface( stone_tile_low, &srect, screen, &drect );

				if( row > 0 && map_[col][row-1] == map.WALL )
				{
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - cam_pos_.y) - TILE_HEIGHT*0.8;
					SDL_BlitSurface( shadow_north, &srect, screen, &drect );
				}
				if( col > 0 && map_[col-1][row] == map.WALL )
				{
					srect.h = 128;
					drect.h = 128;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - cam_pos_.y) -2;
					SDL_BlitSurface( shadow_west, &srect, screen, &drect );
				}
				if( col > 0 && row > 0 && 
					map_[col-1][row-1] == map.WALL && 
					map_[col-1][row] != map.WALL &&
					map_[col][row-1] != map.WALL)
				{
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - cam_pos_.y) - TILE_HEIGHT*0.8;
					SDL_BlitSurface( shadow_north_west, &srect, screen, &drect );
				}
				if( col > 0 && row < MAP_ROWS-1 && 
					map_[col-1][row+1] == map.WALL && 
					map_[col-1][row] != map.WALL)
				{
					srect.h = 128;
					drect.h = 128;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - cam_pos_.y) - TILE_HEIGHT*0.2;
					SDL_BlitSurface( shadow_south_west, &srect, screen, &drect );
				}

				break;
			}

			if( map.getplayer_01_pos_().x == col && map.getplayer_01_pos_().y == row )
			{
				srect.h = 64;
				drect.h = TILE_HEIGHT;
				drect.y = (Sint16)(
					(row * TILE_HEIGHT * 0.75 - cam_pos_.y) - 
					(TILE_HEIGHT * 0.5));
				SDL_BlitSurface( character_player_01, &srect, screen, &drect );
			}
			else if( map.get_players_pos()[0].x == col && map.get_players_pos()[0].y == row )
			{
				srect.h = 64;
				drect.h = TILE_HEIGHT;
				drect.y = (Sint16)(
					(row * TILE_HEIGHT * 0.75 - cam_pos_.y) - 
					(TILE_HEIGHT * 0.5));
				SDL_BlitSurface( character_player_02, &srect, screen, &drect );
			}
		}
	}
}

bool InGameState::isDone()
{
	return false;
}

int InGameState::get_next_state()
{
	return PREGAME;
}
