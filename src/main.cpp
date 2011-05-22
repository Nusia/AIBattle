#pragma once

#include <iostream>
#include "Math.h"
#include "SDL.h"

#include "map/map.h"

int win_width = 800;
int win_height = 600;

const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

bool init_GL()
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

    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    //If everything initialized
    return true;
}

bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    //Create Window
    if( SDL_SetVideoMode( win_width, win_height, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        return false;
    }

    //Initialize OpenGL
    if( init_GL() == false )
    {
        return false;
    }

    //Set caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );

    return true;
}

int main( int argc, char* args[] )
{
	Map map;
	SDL_Event event;

	if( init() )
		std::cout << "Inited properly.\n";
	else
		std::cout << "FAIL!\n";

	bool quit = false;
	while( !quit )
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
				quit = true;

			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				int x_cell = floorf( (event.motion.x / ((float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );
				int y_cell = floorf( (event.motion.y / ((float)(MAP_ROWS*TILE_HEIGHT) / MAP_ROWS) ) );
				map.toggle_active_cell( x_cell, y_cell );
				std::cout << 
					"Mouse button pressed: " << 
					x_cell << 
					", " << 
					y_cell << 
					"\n";
			}
		}

		glClear( GL_COLOR_BUFFER_BIT );

		map.draw();

		//Update Screen
		SDL_GL_SwapBuffers();
	}

	//Quit SDL
    SDL_Quit();

    return 0;
}