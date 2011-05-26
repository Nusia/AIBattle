#include "AIBattle.h"

AIBattle::AIBattle() :
SCREEN_BPP(32), FRAMES_PER_SECOND(60)
{
	win_width = 1024;
	win_height = 768;

	Map map;
	SDL_Event event;
	init();

	bool quit = false;
	while( !quit )
	{
		update();
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

void AIBattle::update()
{
	if( !_tmp_list.empty() )
	{
		map.set_player_01_pos( _tmp_list.front() );
		_tmp_list.erase( _tmp_list.begin() );
	}
}

void AIBattle::handle_event( SDL_Event *event )
{
	AStar a_star( map.get_map(), map.get_players_pos() );
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		Position cell_pos;
		cell_pos.x = (int)floorf(
			( (event->motion.x + map.get_cam_pos().x) / 
			( (float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );

		cell_pos.y = (int)floorf( 
			((event->motion.y + map.get_cam_pos().y) / 
			((float)(MAP_ROWS*TILE_HEIGHT*0.75) / MAP_ROWS) ) );

		if( map.is_pos_walkable( cell_pos ) )
		{
			_tmp_list.clear();
			_tmp_list = a_star.get_best_path( cell_pos, map.get_player_01_pos() );
			_tmp_list.push_back( cell_pos );
		}

		std::cout << 
			"Mouse button pressed: " << 
			cell_pos << "\n";
	}
	map.handle_event( event );
}

void AIBattle::draw()
{
	glClear( GL_COLOR_BUFFER_BIT );

	map.draw( screen );

	SDL_Flip( screen );
	//SDL_GL_SwapBuffers();
}