#include "AIBattle.h"

AIBattle::AIBattle() :
SCREEN_BPP(32), FRAMES_PER_SECOND(60)
{
	win_width = 800;
	win_height = 600;

	Map map;
	SDL_Event event;
	init();

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

    //Initialize OpenGL
    init_GL();

    //Set caption
    SDL_WM_SetCaption( "AIBattle", NULL );
}

void AIBattle::handle_event( SDL_Event *event )
{
	AStar a_star( map.get_map() );
	std::vector< Position > tmp_list;
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		int x_cell = floorf( (event->motion.x / ((float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );
		int y_cell = floorf( (event->motion.y / ((float)(MAP_ROWS*TILE_HEIGHT) / MAP_ROWS) ) );
		tmp_list = a_star.get_best_path( 
			Position( 3, 3 ),
			Position( x_cell, y_cell ) );
		//map.toggle_active_cell( x_cell, y_cell );
		std::cout << 
			"Mouse button pressed: " << 
			x_cell << ", " << 
			y_cell << "\n";

		map.set_path( tmp_list );
		//for( int i = 0; i < tmp_list.size(); ++i )
		//	std::cout << tmp_list[i].x << ", " << tmp_list[0].y << "\n";
	}
}

void AIBattle::draw() const
{
	glClear( GL_COLOR_BUFFER_BIT );

	map.draw();

	SDL_GL_SwapBuffers();
}