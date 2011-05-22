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

	_map[2][0] = 1;
	_map[2][1] = 1;
	_map[2][2] = 1;
	_map[2][3] = 1;
	_map[3][3] = 1;
	_map[2][4] = 1;
	_map[3][6] = 1;
	_map[3][7] = 1;
	_map[3][8] = 1;
	_map[3][9] = 1;
	_map[5][5] = 1;
	_map[6][5] = 1;
	_map[5][6] = 1;
	_map[6][6] = 1;
	_map[4][6] = 1;
	_map[1][4] = 1;
	_map[1][5] = 1;
	_map[1][6] = 1;
	_map[1][7] = 1;
	_map[7][4] = 1;
	_map[8][3] = 1;
	_map[9][6] = 1;
}

void Map::draw()
{
	glClear( GL_COLOR_BUFFER_BIT );

	glPushMatrix();
	glTranslatef( -0.5f, 0.f, 0.f );
	for( int col = 0; col < MAP_COLS; ++col )
	{
		for( int row = 0; row < MAP_ROWS; ++row )
		{
			if( _map[col][row] == 0 )
			{
				glColor3f( 0.f, 1.f, 0.f );
			}
			else
			{
				glColor3f( 1.f, 0.f, 0.f );
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
		_map[x][y] = 1;
}