#include "AIBattle.h"

AIBattle::AIBattle()
{
	win_width = 800;
	win_height = 600;
	SCREEN_BPP = 32;
	FRAMES_PER_SECOND = 60;

	init();
	map = new Map();
}

void AIBattle::init_GL()
{
    //Set clear color
    glClearColor( 0, 0, 0, 0 );

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, win_width, win_height, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void AIBattle::init()
{
    //Initialize SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Create Window
    SDL_SetVideoMode( win_width, win_height, SCREEN_BPP, SDL_OPENGL );

    //Set caption
    SDL_WM_SetCaption( "AIBattle", NULL );
}

void AIBattle::handle_events( SDL_Event *event )
{
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		int x_cell = floorf( (event->motion.x / ((float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );
		int y_cell = floorf( (event->motion.y / ((float)(MAP_ROWS*TILE_HEIGHT) / MAP_ROWS) ) );
		map->toggle_active_cell( x_cell, y_cell );
		std::cout << 
			"Mouse button pressed: " << 
			x_cell << ", " << 
			y_cell << "\n";
	}
}

void AIBattle::draw()
{
	
	glClear( GL_COLOR_BUFFER_BIT );

	map->draw();

	//Reset
	glLoadIdentity();

	//Update Screen
	SDL_GL_SwapBuffers();
}