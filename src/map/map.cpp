#include "map.h"

Map::Map()
{
}
//
void Map::init()
{
	std::cout << "Initiating map.\n";
	player_01_pos_ = Position( 0, 0 );
	player_02_pos_ = Position( 0, 1 );

	load_map();

	std::cout << "Map ready.\n";
}
//
void Map::update()
{
}
//
void Map::draw( SDL_Surface* screen )
{
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
}