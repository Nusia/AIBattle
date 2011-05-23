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

	_map[19][16] = WALL;

	_map[20][20] = WALL;
	_map[21][20] = WALL;
	_map[22][20] = WALL;
	_map[23][20] = WALL;

	_map[20][21] = WALL;
	_map[21][21] = WALL;
	_map[22][21] = WALL;
	_map[23][21] = WALL;

	_map[20][22] = WALL;
	_map[21][22] = WALL;
	_map[22][22] = WALL;
	_map[23][22] = WALL;

	_map[20][23] = WALL;
	_map[21][23] = WALL;
	_map[22][23] = WALL;
	_map[23][23] = WALL;

	_map[10][10] = WALL;
	_map[11][10] = WALL;
	_map[12][10] = WALL;
	_map[13][10] = WALL;

	_map[10][11] = WALL;
	_map[11][11] = WALL;
	_map[12][11] = WALL;
	_map[13][11] = WALL;

	_map[10][12] = WALL;
	_map[11][12] = WALL;
	_map[12][12] = WALL;
	_map[13][12] = WALL;

	_map[10][13] = WALL;
	_map[11][13] = WALL;
	_map[12][13] = WALL;
	_map[13][13] = WALL;

	_map[58][40] = WALL;
	_map[58][41] = WALL;
	_map[58][42] = WALL;
	_map[58][43] = WALL;
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

	glColor3f( 0.f, 0.f, 0.f );
	for( int i = 0; i < _path.size(); ++i )
	{
		glBegin( GL_POLYGON );
		glVertex3f( _path[i].x * TILE_WIDTH, _path[i].y * TILE_HEIGHT, 0.f );
		glVertex3f( _path[i].x * TILE_WIDTH, (_path[i].y+1) * TILE_HEIGHT, 0.f );
		glVertex3f( (_path[i].x+1) * TILE_WIDTH, (_path[i].y+1) * TILE_HEIGHT, 0.f );
		glVertex3f( (_path[i].x+1) * TILE_WIDTH, _path[i].y * TILE_HEIGHT, 0.f );
		glEnd();

	}
	glPopMatrix();
}

void Map::toggle_active_cell( int x, int y )
{
	if( x < MAP_COLS && y < MAP_ROWS )
	{
		if( _map[x][y] == WALKABLE )
			_map[x][y] = WALL;
		else if( _map[x][y] == WALL )
			_map[x][y] = WALKABLE;
	}
}