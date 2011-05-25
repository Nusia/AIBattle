#include "AIBattleMapedit.h"

AIBattleMapedit::AIBattleMapedit() :
SCREEN_BPP(32), FRAMES_PER_SECOND(60)
{
	win_width = MAP_COLS*TILE_WIDTH;
	win_height = MAP_ROWS*TILE_HEIGHT + 120;

	active_block_type = Map::WALKABLE;
	Map map;
	SDL_Event event;
	init();

	if( TTF_Init() == -1 )
    {
		std::cout << "Could not init TTF.\n";
    }

	font = TTF_OpenFont( "Nilland.ttf", 14 );
	if( font == NULL )
		std::cout << "Font not found: " << TTF_GetError() << "\n";
	else
		std::cout << "Font found.\n";

	bool quit = false;
	while( !quit )
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT || 
				( event.type == SDL_KEYDOWN && 
				  event.key.keysym.sym == SDLK_ESCAPE )
				)
				quit = true;
			else
				handle_event( &event );
		}

		draw();
	}

	//Quit SDL
    SDL_Quit();

}

void AIBattleMapedit::init_GL()
{
    //Set clear color
    glClearColor( 1, 1, 1, 0 );

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, win_width, win_height, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void AIBattleMapedit::init()
{
    //Initialize SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Create Window
    screen = SDL_SetVideoMode( win_width, win_height, SCREEN_BPP, SDL_OPENGL );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    //Initialize OpenGL
    init_GL();

    //Set caption
    SDL_WM_SetCaption( "AIBattleMapedit", NULL );
}

void AIBattleMapedit::handle_event( SDL_Event *event )
{
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		int x_cell = floorf( (event->motion.x / ((float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );
		int y_cell = floorf( (event->motion.y / ((float)(MAP_ROWS*TILE_HEIGHT) / MAP_ROWS) ) );
		
		map.toggle_active_cell( active_block_type, Position( x_cell, y_cell ) );

		std::cout << 
			"Mouse button pressed: " << 
			x_cell << ", " << 
			y_cell << "\n";
	}

	if( event->type == SDL_KEYDOWN )
	{
		switch( event->key.keysym.sym )
		{
		case SDLK_0:
			active_block_type = Map::WALKABLE;
			break;

		case SDLK_1:
			active_block_type = Map::WALL;
			break;

		case SDLK_2:
			active_block_type = Map::PLAYER01;
			break;

		case SDLK_3:
			active_block_type = Map::PLAYER02;
			break;
		case SDLK_s:
			map.save_map();
			break;
		case SDLK_l:
			map.load_map();
			break;
		case SDLK_r:
			map.reset_map();
			break;
		}
	}
}

void AIBattleMapedit::RenderText(
		const TTF_Font *Font, 
		const float R, 
		const float G, 
		const float B, 
		const double& X, 
		const double& Y, 
		const double& Z, 
		const std::string& Text)
{
	/*Create some variables.*/
	
	SDL_Color c = {255, 255, 255};
	SDL_Surface *Message = TTF_RenderText_Blended(
		const_cast<TTF_Font*>(Font), 
		Text.c_str(), 
		c);

	unsigned Texture = 0;
 
	/*Generate an OpenGL 2D texture from the SDL_Surface*.*/
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		Message->w, 
		Message->h, 
		0,
		GL_BGRA, 
		GL_UNSIGNED_BYTE, 
		Message->pixels);
 
	/*Draw this texture on a quad with the given xyz coordinates.*/
	glColor3f( R, G, B );
	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3d(X, Y, Z);
		glTexCoord2d(1, 0); glVertex3d(X+Message->w, Y, Z);
		glTexCoord2d(1, 1); glVertex3d(X+Message->w, Y+Message->h, Z);
		glTexCoord2d(0, 1); glVertex3d(X, Y+Message->h, Z);
	glEnd();
 
	/*Clean up.*/
	glDeleteTextures(1, &Texture);
	SDL_FreeSurface(Message);
}


void AIBattleMapedit::draw()
{
	glClearColor( 0.0f, 0.f, 0.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT );

	map.draw();

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		40, MAP_ROWS*TILE_HEIGHT + 50, 0, 
		"Use your keyboard n00b!!! >_<" );

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		300, MAP_ROWS*TILE_HEIGHT + 20, 0, 
		"0: Change active tile to 'Walkable'" );

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		300, MAP_ROWS*TILE_HEIGHT + 40, 0, 
		"1: Change active tile to 'Wall'" );

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		300, MAP_ROWS*TILE_HEIGHT + 60, 0, 
		"2: Change active tile to 'Player #1'" );

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		300, MAP_ROWS*TILE_HEIGHT + 80, 0, 
		"3: Change active tile to 'Player #2'" );

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		600, MAP_ROWS*TILE_HEIGHT + 20, 0, 
		"S: Save map" );

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		600, MAP_ROWS*TILE_HEIGHT + 40, 0, 
		"L: Load map" );

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		600, MAP_ROWS*TILE_HEIGHT + 60, 0, 
		"R: Reset map" );

	RenderText( 
		font, 
		1.0f, 1.0f, 1.0f, 
		600, MAP_ROWS*TILE_HEIGHT + 80, 0, 
		"ESC: Quit" );

	SDL_GL_SwapBuffers();
}

void reset_map()
{

}