#include "map.h"

Map::Map()
{
	std::vector<int> tmp;
	for( int col = 0; col < MAP_COLS; ++col )
	{
		tmp.clear();
		for( int row = 0; row < MAP_ROWS; ++row ) 
			tmp.push_back( 0 );
		_map.push_back( tmp );
	}

	_map[2][0] = WALL;
	_map[2][1] = WALL;
	_map[2][2] = WALL;
	_map[2][3] = WALL;
	_map[3][3] = WALL;
	_map[2][4] = WALL;
	_map[3][6] = WALL;
	_map[3][7] = WALL;
	_map[3][8] = WALL;
	_map[3][9] = WALL;
	_map[5][5] = WALL;
	_map[6][5] = WALL;
	_map[5][6] = WALL;
	_map[6][6] = WALL;
	_map[4][6] = WALL;
	_map[1][4] = WALL;
	_map[1][5] = WALL;
	_map[1][6] = WALL;
	_map[1][7] = WALL;
	_map[7][4] = WALL;
	_map[8][3] = WALL;
	_map[9][6] = WALL;
	_map[30][15] = UNIT;
}

void Map::draw() const
{
	glClear( GL_COLOR_BUFFER_BIT );

	glPushMatrix();
	glTranslatef( -0.5f, 0.f, 0.f );
	for( int col = 0; col < MAP_COLS; ++col )
	{
		for( int row = 0; row < MAP_ROWS; ++row )
		{
			switch( _map[col][row] )
			{
			case WALL: 
				glColor3f( 1.f, 0.f, 0.f );
				break;
			case WALKABLE:
				glColor3f( 0.f, 1.f, 0.f );
				break;
			case UNIT:
				glColor3f( 0.f, 0.f, 1.f );
				break;
			}

			glBegin( GL_POLYGON );
			glVertex3f( col * TILE_WIDTH, row * TILE_HEIGHT, 0.f );
			glVertex3f( col * TILE_WIDTH, (row+1) * TILE_HEIGHT, 0.f );
			glVertex3f( (col+1) * TILE_WIDTH, (row+1) * TILE_HEIGHT, 0.f );
			glVertex3f( (col+1) * TILE_WIDTH, row * TILE_HEIGHT, 0.f );
			glEnd();
		}
	}
	glPopMatrix();
}

void Map::toggle_active_cell( int x, int y )
{
	if( x < MAP_COLS && y < MAP_ROWS )
		_map[x][y] = WALL;
}