#include "cMap.h"

cMap::cMap()
{
}
//
void cMap::Init()
{
	std::cout << "Initiating map.\n";
	_player01Pos = cPosition( 0, 0 );
	_player02Pos = cPosition( 0, 1 );

	_loadMap();

	std::cout << "Map ready.\n";
}
//
void cMap::Update()
{
}
//
void cMap::Draw( SDL_Surface* screen )
{
}
//
bool cMap::IsPosWalkable( cPosition pos )
{
	return _vMap[pos.x][pos.y] == WALKABLE;
}
//
void cMap::_loadMap()
{
	std::cout << "Loading saved map.\n";
	std::ifstream infile;
	infile.open( "bin/saved_maps/map01" );
	if( infile.good() )
	{
		_vMap.clear();
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
					_player01Pos.x = col;
					_player01Pos.y = row;
					tmp.push_back( 0 );
				}
				else if ( c == PLAYER02 )
				{
					_player02Pos.x = col;
					_player02Pos.y = row;
					tmp.push_back( 0 );
				}
				else
					tmp.push_back( c );
			}
			_vMap.push_back( tmp );
		}
	}
	else
	{
		std::cout << "Map not found. Generating new map.\n";
		_resetMap();
	}

	infile.close();
}
//
void cMap::_resetMap()
{
	_vMap.clear();
	std::vector<int> tmp;
	for( int col = 0; col < MAP_COLS; ++col )
	{
		tmp.clear();
		for( int row = 0; row < MAP_ROWS; ++row ) 
			tmp.push_back( 0 );
		_vMap.push_back( tmp );
	}
}
//
std::vector<cPosition> cMap::GetPlayersPos()
{
	//TODO: This will have to check what unit that wanna move and
	//return the cPositions of all units but himself.

	std::vector<cPosition> tmp_list;
	//tmp_list.push_back( _player01Pos );
	tmp_list.push_back( _player02Pos );
	return tmp_list;
}
//
//  TMP *****
//
void cMap::HandleEvent( SDL_Event *event )
{
}