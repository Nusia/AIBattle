#include "map.h"

Map::Map()
{
	_cam_pos = Position(0, 0);
	_unit_pos = Position( 4, 4 );
	character_basic = load_image("../resources/character_basic.png");
	stone_tile_low = load_image("../resources/stone_tile_low_64.png");
	stone_tile_high = load_image("../resources/stone_tile_high_64.png");
	//load_image( "../resources/stone_tile_low_64_bmp.bmp" );

	std::vector<int> tmp;
	for( int col = 0; col < MAP_COLS; ++col )
	{
		tmp.clear();
		for( int row = 0; row < MAP_ROWS; ++row ) 
			tmp.push_back( 0 );
		_map.push_back( tmp );
	}

	_map[5][5] = WALL;
	_map[6][5] = WALL;

	_map[4][5] = WALL;
	_map[4][6] = WALL;
	_map[4][7] = WALL;
	_map[4][8] = WALL;

	_map[8][6] = WALL;
	_map[8][7] = WALL;
	_map[8][8] = WALL;
	_map[8][9] = WALL;

	_map[9][6] = WALL;
	_map[9][9] = WALL;

	_map[10][6] = WALL;
	_map[10][9] = WALL;

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

void Map::draw( SDL_Surface* screen )
{


	/*glClear( GL_COLOR_BUFFER_BIT );
	glPushMatrix();
	glTranslatef( -_cam_pos.x, -_cam_pos.y, 0.f );*/

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture( GL_TEXTURE_2D, texture );

	SDL_Rect srect, drect;
	srect.x = 0;
	srect.y = 0;
	srect.w = TILE_WIDTH;
	drect.w = TILE_WIDTH;

	for( int col = 0; col < MAP_COLS; ++col )
	{
		for( int row = 0; row < MAP_ROWS; ++row )
		{
			srect.h = 64;
			drect.h = 64;
			drect.x = col * TILE_WIDTH - _cam_pos.x; 
			drect.y = (row * TILE_HEIGHT * 0.75 - _cam_pos.y);

			switch( _map[col][row] )
			{
			case WALL: 
				srect.h = 128;
				drect.h = 128;
				drect.y -= 64;
				SDL_BlitSurface( stone_tile_high, &srect, screen, &drect );
				break;

			case WALKABLE:
				drect.y -= 14;
				SDL_BlitSurface( stone_tile_low, &srect, screen, &drect );
				break;
			}

			if( _unit_pos.x == col && _unit_pos.y == row )
			{
				srect.h = 64;
				drect.h = 64;
				drect.y = 
					(row * TILE_HEIGHT * 0.75 - _cam_pos.y) - 
					TILE_HEIGHT * 0.5;
				SDL_BlitSurface( character_basic, &srect, screen, &drect );
			}

		}
	}

	//glColor3f( 0.f, 1.f, 0.f );
	//for( int i = 0; i < _path.size(); ++i )
	//{
	//	glBegin( GL_POLYGON );
	//	glVertex3f( _path[i].x * TILE_WIDTH, _path[i].y * TILE_HEIGHT, 0.f );
	//	glVertex3f( _path[i].x * TILE_WIDTH, (_path[i].y+1) * TILE_HEIGHT, 0.f );
	//	glVertex3f( (_path[i].x+1) * TILE_WIDTH, (_path[i].y+1) * TILE_HEIGHT, 0.f );
	//	glVertex3f( (_path[i].x+1) * TILE_WIDTH, _path[i].y * TILE_HEIGHT, 0.f );
	//	glEnd();
	//}

	//glColor3f( 0.f, 0.f, 0.f );
	//for( int col = 0; col < MAP_COLS; ++col )
	//{
	//	glBegin( GL_LINES );
	//	glVertex3f( col * TILE_WIDTH, 0.f, 0.f );
	//	glVertex3f( col * TILE_WIDTH, MAP_ROWS * TILE_HEIGHT, 0.f );
	//	glEnd();
	//}
	//for( int row = 0; row < MAP_ROWS; ++row )
	//{
	//	glBegin( GL_LINES );
	//	glVertex3f( 0.f, row * TILE_HEIGHT, 0.f );
	//	glVertex3f( MAP_COLS * TILE_WIDTH, row * TILE_HEIGHT, 0.f );
	//	glEnd();
	//}

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

SDL_Surface* Map::load_image( char *file ) 
{
	SDL_Surface *tmp;
	tmp = IMG_Load(file);

	if (tmp == NULL) {
		std::cout << "Error: '%s' could not be opened: " << file << IMG_GetError() << "\n";
	} else {
		if(SDL_SetColorKey(tmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tmp->format, COLORKEY)) == -1)
			std::cout << "Warning: colorkey will not be used, reason: " << SDL_GetError() << "\n";
	}
	return tmp;
}

bool Map::is_pos_walkable( Position pos )
{
	return _map[pos.x][pos.y] == WALKABLE;
}

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
