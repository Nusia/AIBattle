#include "map.h"

Map::Map()
{
}
//
void Map::init()
{
	std::cout << "Initiating map.\n";
	cam_pos_ = Position(0, 0);
	player_01_pos_ = Position( 0, 0 );
	player_01_pos_ = Position( 0, 1 );

	load_map();

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
	std::cout << "Map ready.\n";
}
//
void Map::update()
{
}
//
void Map::draw( SDL_Surface* screen )
{
	SDL_Rect srect, drect;
	srect.x = 0;
	srect.y = 0;
	srect.w = 64;
	drect.w = TILE_WIDTH;

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
			case WALL: 
				srect.h = 128;
				drect.h = TILE_HEIGHT*2;
				drect.y -= TILE_HEIGHT;
				SDL_BlitSurface( stone_tile_high, &srect, screen, &drect );

				if( col > 0 && row > 0 &&
					map_[col-1][row] != WALL && 
					map_[col][row-1] != WALL )
				{
					drect.x = (col-1) * TILE_WIDTH - cam_pos_.x;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - cam_pos_.y);
					SDL_BlitSurface( shadow_south_east, &srect, screen, &drect );
				}
				if( col > 0 &&
					map_[col-1][row] != WALL )
				{
					srect.h = TILE_HEIGHT*1.35;
					drect.h = TILE_HEIGHT*1.35;
					drect.x = (col-1) * TILE_WIDTH - cam_pos_.x;
					drect.y = (Sint16)((row-1)*TILE_HEIGHT*0.75 - cam_pos_.y) - 2;
					SDL_BlitSurface( shadow_east, &srect, screen, &drect );
				}
				if( row > 0 &&
					map_[col][row-1] != WALL )
				{
					drect.x = (col) * TILE_WIDTH - cam_pos_.x;
					drect.y = (Sint16)((row-2) * TILE_HEIGHT * 0.75 - cam_pos_.y) - TILE_HEIGHT*0.15;
					SDL_BlitSurface( shadow_south, &srect, screen, &drect );
				}
				if( col > 0 && row < MAP_ROWS-1 &&
					map_[col-1][row+1] != WALL && 
					map_[col][row+1] != WALL &&
					map_[col-1][row] != WALL)
				{
					drect.x = (col-1) * TILE_WIDTH - cam_pos_.x;
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - cam_pos_.y) -2;
					SDL_BlitSurface( shadow_north_east, &srect, screen, &drect );
				}
				break;

			case WALKABLE:
				drect.h = TILE_HEIGHT;
				drect.y -= (Sint16)(TILE_HEIGHT * 0.25);
				SDL_BlitSurface( stone_tile_low, &srect, screen, &drect );

				if( row > 0 && map_[col][row-1] == WALL )
				{
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - cam_pos_.y) - TILE_HEIGHT*0.8;
					SDL_BlitSurface( shadow_north, &srect, screen, &drect );
				}
				if( col > 0 && map_[col-1][row] == WALL )
				{
					srect.h = 128;
					drect.h = 128;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - cam_pos_.y) -2;
					SDL_BlitSurface( shadow_west, &srect, screen, &drect );
				}
				if( col > 0 && row > 0 && 
					map_[col-1][row-1] == WALL && 
					map_[col-1][row] != WALL &&
					map_[col][row-1] != WALL)
				{
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - cam_pos_.y) - TILE_HEIGHT*0.8;
					SDL_BlitSurface( shadow_north_west, &srect, screen, &drect );
				}
				if( col > 0 && row < MAP_ROWS-1 && 
					map_[col-1][row+1] == WALL && 
					map_[col-1][row] != WALL)
				{
					srect.h = 128;
					drect.h = 128;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - cam_pos_.y) - TILE_HEIGHT*0.2;
					SDL_BlitSurface( shadow_south_west, &srect, screen, &drect );
				}

				break;
			}

			if( player_01_pos_.x == col && player_01_pos_.y == row )
			{
				srect.h = 64;
				drect.h = TILE_HEIGHT;
				drect.y = (Sint16)(
					(row * TILE_HEIGHT * 0.75 - cam_pos_.y) - 
					(TILE_HEIGHT * 0.5));
				SDL_BlitSurface( character_player_01, &srect, screen, &drect );
			}
			else if( player_02_pos_.x == col && player_02_pos_.y == row )
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
//
bool Map::is_pos_walkable( Position pos )
{
	return map_[pos.x][pos.y] == WALKABLE;
}
//
void Map::load_map()
{
	std::cout << "Loading saved map.\n";
	std::ifstream infile;
	infile.open( "../bin/saved_maps/map01" );
	if( infile.good() )
	{
		map_.clear();
		std::vector<int> tmp;
		char c;
		for( int col = 0; col < MAP_COLS; ++col )
		{
			tmp.clear();
			for( int row = 0; row < MAP_ROWS; ++row )
			{
				infile >> c;
				c -= 48;
				if ( c == PLAYER01 )
				{
					player_01_pos_.x = col;
					player_01_pos_.y = row;
					tmp.push_back( 0 );
				}
				else if ( c == PLAYER02 )
				{
					player_02_pos_.x = col;
					player_02_pos_.y = row;
					tmp.push_back( 0 );
				}
				else
					tmp.push_back( c );
			}
			map_.push_back( tmp );
		}
	}
	else
	{
		std::cout << "Map not found. Generating new map.\n";
		reset_map();
	}

	infile.close();
}
//
void Map::reset_map()
{
	map_.clear();
	std::vector<int> tmp;
	for( int col = 0; col < MAP_COLS; ++col )
	{
		tmp.clear();
		for( int row = 0; row < MAP_ROWS; ++row ) 
			tmp.push_back( 0 );
		map_.push_back( tmp );
	}
}
//
std::vector<Position> Map::get_players_pos()
{
	//TODO: This will have to check what unit that wanna move and
	//return the positions of all units but himself.

	std::vector<Position> tmp_list;
	//tmp_list.push_back( player_01_pos_ );
	tmp_list.push_back( player_02_pos_ );
	return tmp_list;
}
//
//  TMP *****
//
void Map::handle_event( SDL_Event *event )
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
}