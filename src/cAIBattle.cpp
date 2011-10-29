#include "cAIBattle.h"

cAIBattle::cAIBattle() :
SCREEN_BPP(32), FRAMES_PER_SECOND(60)
{
	_nWinWidth = 1024;
	_nWinHeight = 768;

	SDL_Event event;
	_init();

	bool quit = false;
	while( !quit )
	{
		_GameStateManager.Update();
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT || 
				( event.type == SDL_KEYDOWN && 
				  event.key.keysym.sym == SDLK_ESCAPE )
				)
				quit = true;
			else
				_GameStateManager.HandleInput( &event );
		}
		Draw();
	}

	//Quit SDL
    SDL_Quit();

}

void cAIBattle::_initGL()
{
    //Set clear color
    glClearColor( 0, 0, 0, 0 );

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, _nWinWidth, _nWinHeight, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void cAIBattle::_init()
{
    //Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Init( SDL_INIT_EVERYTHING );

	atexit(SDL_Quit);

    //Create Window
	_pScreen = SDL_SetVideoMode( _nWinWidth, _nWinHeight, SCREEN_BPP, SDL_DOUBLEBUF | SDL_SWSURFACE );

    //Initialize OpenGL
    _initGL();

    //Set caption
    SDL_WM_SetCaption( "AIBattle", NULL );
}

void cAIBattle::Draw()
{
	SDL_FillRect( _pScreen,NULL, 0x000000 ); //Clear screen

	_GameStateManager.Draw( _pScreen );

	SDL_Flip( _pScreen );
}