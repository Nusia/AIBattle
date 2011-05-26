#include "AIBattle.h"

AIBattle::AIBattle() :
SCREEN_BPP(32), FRAMES_PER_SECOND(60)
{
	win_width = 1024;
	win_height = 768;

	SDL_Event event;
	init();

	bool quit = false;
	while( !quit )
	{
		_game_state_manager.update();
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT || 
				( event.type == SDL_KEYDOWN && 
				  event.key.keysym.sym == SDLK_ESCAPE )
				)
				quit = true;
			else
				_game_state_manager.handle_input( &event );
		}
		draw();
	}

	//Quit SDL
    SDL_Quit();

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
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Init( SDL_INIT_EVERYTHING );

	atexit(SDL_Quit);

    //Create Window
	screen = SDL_SetVideoMode( win_width, win_height, SCREEN_BPP, SDL_DOUBLEBUF | SDL_SWSURFACE );

    //Initialize OpenGL
    init_GL();

    //Set caption
    SDL_WM_SetCaption( "AIBattle", NULL );
}

void AIBattle::draw()
{
	glClear( GL_COLOR_BUFFER_BIT );

	_game_state_manager.draw( screen );

	SDL_Flip( screen );
	//SDL_GL_SwapBuffers();
}