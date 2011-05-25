#include "map.h"

Map::Map()
{
	load_map();

	tile_type_name[0] = "Walkable";
	tile_type_name[1] = "Wall";
	tile_type_name[2] = "Player 1";
	tile_type_name[3] = "Player 2";
}

void Map::draw() const
{
	//glClear( GL_COLOR_BUFFER_BIT );

	glPushMatrix();
	//glTranslatef( -0.5f, 0.f, 0.f );
	for( int col = 0; col < MAP_COLS; ++col )
	{
		for( int row = 0; row < MAP_ROWS; ++row )
		{
			switch( _map[col][row] )
			{
			case WALL: 
				glColor3f( 0.f, 0.f, 0.f );
				break;

			case WALKABLE:
				glColor3f( 1.f, 1.f, 1.f );
				break;

			case PLAYER01:
				glColor3f( 0.f, 1.f, 0.f );
				break;

			case PLAYER02:
				glColor3f( 1.f, 0.f, 0.f );
				break;
			}

			glBegin( GL_POLYGON );
			glVertex3f( col * TILE_WIDTH, row * TILE_HEIGHT, 0.f );
			glVertex3f( col * TILE_WIDTH, (row+1) * TILE_HEIGHT, 0.f );
			glVertex3f( (col+1) * TILE_WIDTH, (row+1) * TILE_HEIGHT, 0.f );
			glVertex3f( (col+1) * TILE_WIDTH, row * TILE_HEIGHT, 0.f );
			glEnd();

			if( col == MAP_COLS-1 )
			{
				glColor3f( 0.f, 0.f, 0.f );
				glBegin( GL_LINES );
				glVertex3f( 0.f, row*TILE_HEIGHT, 0.f );
				glVertex3f( MAP_COLS*TILE_WIDTH, row*TILE_HEIGHT, 0.f );
				glEnd();
			}
		}
		glColor3f( 0.f, 0.f, 0.f );
		glBegin( GL_LINES );
		glVertex3f( col*TILE_WIDTH, 0.f, 0.f );
		glVertex3f( col*TILE_WIDTH, MAP_ROWS*TILE_HEIGHT, 0.f );
		glEnd();
	}



	glPopMatrix();
}

void Map::toggle_active_cell( int type, Position pos )
{
	if( pos.x < MAP_COLS && pos.y < MAP_ROWS )
	{
		if( _map[pos.x][pos.y] != PLAYER01 &&
			_map[pos.x][pos.y] != PLAYER02 )
		{
			_map[pos.x][pos.y] = type;
			if( type == Map::PLAYER01 )
			{
				_map[_player_01_pos.x][_player_01_pos.y] = Map::WALKABLE;
				_player_01_pos = pos;
			}
			else if( type == Map::PLAYER02 )
			{
				_map[_player_02_pos.x][_player_02_pos.y] = Map::WALKABLE;
				_player_02_pos = pos;
			}
		}

	}
}

void Map::save_map()
{
	std::ofstream outfile;
	outfile.open( "../saved_maps/map01" );
	outfile.clear();

	for( int col = 0; col < MAP_COLS; ++col )
	{
		for( int row = 0; row < MAP_ROWS; ++row ) 
			outfile << _map[col][row];
	}

	outfile.close();
}

void Map::load_map()
{
	std::ifstream infile;
	infile.open( "../saved_maps/map01" );
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
					_player_01_pos = Position( col, row );
				if ( c == PLAYER02 )
					_player_02_pos = Position( col, row );
				tmp.push_back( c );
			}
			_map.push_back( tmp );
		}

		infile.close();
	}
	else
		reset_map();
}

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

	_player_01_pos = Position( 1, 0 );
	_player_02_pos = Position( 1, 1 );
	toggle_active_cell( PLAYER01, Position(0,0) );
	toggle_active_cell( PLAYER02, Position(0,1) );
}