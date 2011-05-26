#include "map.h"

Map::Map()
{
	_cam_pos = Position(0, 0);
	_player_01_pos = Position( 0, 0 );
	_player_01_pos = Position( 0, 1 );

	load_map();

	character_player_01 = load_image("../resources/character_basic_green.png");
	character_player_02 = load_image("../resources/character_basic_red.png");
	stone_tile_low = load_image("../resources/stone_tile_low_64.png");
	stone_tile_high = load_image("../resources/stone_tile_high_64.png");

	shadow_north_east = load_image("../resources/shadow_north_east.png");
	shadow_east = load_image("../resources/shadow_east.png");
	shadow_south_east = load_image("../resources/shadow_south_east.png");	
	shadow_south = load_image("../resources/shadow_south.png");
	shadow_south_west = load_image("../resources/shadow_south_west.png");
	shadow_west = load_image("../resources/shadow_west.png");
	shadow_north_west = load_image("../resources/shadow_north_west.png");
	shadow_north = load_image("../resources/shadow_north.png");
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
			drect.x = col * TILE_WIDTH - _cam_pos.x; 
			drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - _cam_pos.y);

			switch( _map[col][row] )
			{
			case WALL: 
				srect.h = 128;
				drect.h = TILE_HEIGHT*2;
				drect.y -= TILE_HEIGHT;
				SDL_BlitSurface( stone_tile_high, &srect, screen, &drect );

				if( col > 0 && row > 0 &&
					_map[col-1][row] != WALL && 
					_map[col][row-1] != WALL )
				{
					drect.x = (col-1) * TILE_WIDTH - _cam_pos.x;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - _cam_pos.y);
					SDL_BlitSurface( shadow_south_east, &srect, screen, &drect );
				}
				if( col > 0 &&
					_map[col-1][row] != WALL )
				{
					srect.h = TILE_HEIGHT*1.35;
					drect.h = TILE_HEIGHT*1.35;
					drect.x = (col-1) * TILE_WIDTH - _cam_pos.x;
					drect.y = (Sint16)((row-1)*TILE_HEIGHT*0.75 - _cam_pos.y) - 2;
					SDL_BlitSurface( shadow_east, &srect, screen, &drect );
				}
				if( row > 0 &&
					_map[col][row-1] != WALL )
				{
					drect.x = (col) * TILE_WIDTH - _cam_pos.x;
					drect.y = (Sint16)((row-2) * TILE_HEIGHT * 0.75 - _cam_pos.y) - TILE_HEIGHT*0.15;
					SDL_BlitSurface( shadow_south, &srect, screen, &drect );
				}
				if( col > 0 && row < MAP_ROWS-1 &&
					_map[col-1][row+1] != WALL && 
					_map[col][row+1] != WALL &&
					_map[col-1][row] != WALL)
				{
					drect.x = (col-1) * TILE_WIDTH - _cam_pos.x;
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - _cam_pos.y) -2;
					SDL_BlitSurface( shadow_north_east, &srect, screen, &drect );
				}
				break;

			case WALKABLE:
				drect.h = TILE_HEIGHT;
				drect.y -= (Sint16)(TILE_HEIGHT * 0.25);
				SDL_BlitSurface( stone_tile_low, &srect, screen, &drect );

				if( row > 0 && _map[col][row-1] == WALL )
				{
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - _cam_pos.y) - TILE_HEIGHT*0.8;
					SDL_BlitSurface( shadow_north, &srect, screen, &drect );
				}
				if( col > 0 && _map[col-1][row] == WALL )
				{
					srect.h = 128;
					drect.h = 128;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - _cam_pos.y) -2;
					SDL_BlitSurface( shadow_west, &srect, screen, &drect );
				}
				if( col > 0 && row > 0 && 
					_map[col-1][row-1] == WALL && 
					_map[col-1][row] != WALL &&
					_map[col][row-1] != WALL)
				{
					drect.y = (Sint16)(row * TILE_HEIGHT * 0.75 - _cam_pos.y) - TILE_HEIGHT*0.8;
					SDL_BlitSurface( shadow_north_west, &srect, screen, &drect );
				}
				if( col > 0 && row < MAP_ROWS-1 && 
					_map[col-1][row+1] == WALL && 
					_map[col-1][row] != WALL)
				{
					srect.h = 128;
					drect.h = 128;
					drect.y = (Sint16)((row-1) * TILE_HEIGHT * 0.75 - _cam_pos.y) - TILE_HEIGHT*0.2;
					SDL_BlitSurface( shadow_south_west, &srect, screen, &drect );
				}

				break;
			}

			if( _player_01_pos.x == col && _player_01_pos.y == row )
			{
				srect.h = 64;
				drect.h = TILE_HEIGHT;
				drect.y = (Sint16)(
					(row * TILE_HEIGHT * 0.75 - _cam_pos.y) - 
					(TILE_HEIGHT * 0.5));
				SDL_BlitSurface( character_player_01, &srect, screen, &drect );
			}
			else if( _player_02_pos.x == col && _player_02_pos.y == row )
			{
				srect.h = 64;
				drect.h = TILE_HEIGHT;
				drect.y = (Sint16)(
					(row * TILE_HEIGHT * 0.75 - _cam_pos.y) - 
					(TILE_HEIGHT * 0.5));
				SDL_BlitSurface( character_player_02, &srect, screen, &drect );
			}
		}
	}
}
//
SDL_Surface* Map::load_image( char *file ) 
{
	SDL_Surface *tmp;
	tmp = IMG_Load(file);

	if (tmp == NULL) {
		std::cout << "Error: Could not open " << file << ". " << IMG_GetError() << "\n";
	} else {
		if(SDL_SetColorKey(tmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tmp->format, COLORKEY)) == -1)
			std::cout << "Warning: colorkey will not be used, reason: " << SDL_GetError() << "\n";
	}
	return tmp;
}
//
bool Map::is_pos_walkable( Position pos )
{
	return _map[pos.x][pos.y] == WALKABLE;
}
//
void Map::load_map()
{
	std::ifstream infile;
	infile.open( "../bin/saved_maps/map01" );
	if( infile.good() )
	{
		_map.clear();
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
					_player_01_pos.x = col;
					_player_01_pos.y = row;
					tmp.push_back( 0 );
				}
				else if ( c == PLAYER02 )
				{
					_player_02_pos.x = col;
					_player_02_pos.y = row;
					tmp.push_back( 0 );
				}
				else
					tmp.push_back( c );
			}
			_map.push_back( tmp );
		}
	}
	else
		reset_map();

	infile.close();
}
//
void Map::reset_map()
{
	_map.clear();
	std::vector<int> tmp;
	for( int col = 0; col < MAP_COLS; ++col )
	{
		tmp.clear();
		for( int row = 0; row < MAP_ROWS; ++row ) 
			tmp.push_back( 0 );
		_map.push_back( tmp );
	}
}
//
std::vector<Position> Map::get_players_pos()
{
	//TODO: This will have to check what unit that wanna move and
	//return the positions of all units but himself.

	std::vector<Position> tmp_list;
	//tmp_list.push_back( _player_01_pos );
	tmp_list.push_back( _player_02_pos );
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
			_cam_pos.y += 25;
		if( event->key.keysym.sym == SDLK_UP && _cam_pos.y > 0 )
			_cam_pos.y -= 25;
		if( event->key.keysym.sym == SDLK_RIGHT )
			_cam_pos.x += 25;
		if( event->key.keysym.sym == SDLK_LEFT && _cam_pos.x > 0)
			_cam_pos.x -= 25;
	}
}