#include "map_settings.h"

MapSettings::MapSettings()
: TILE_SIZE(16)
{
	map_.init();
	map_x_offset = 1024/2 - (MAP_COLS*TILE_SIZE)/2;
	map_y_offset = 68;

	font = TextHandler::get_font( "../resources/fonts/larabiefont_rg.ttf", 16 );
	white_tex_ = ImageHelper::load_image( "../resources/pre_game/white.bmp" );
	black_tex_ = ImageHelper::load_image( "../resources/pre_game/black.bmp" );
	red_tex_ = ImageHelper::load_image( "../resources/pre_game/red.bmp" );
	green_tex_ = ImageHelper::load_image( "../resources/pre_game/green.bmp" );
	blue_tex_ = ImageHelper::load_image( "../resources/pre_game/blue.bmp" );	
}

void MapSettings::handle_input( SDL_Event* event )
{
	AStar a_star( map_.get_map(), map_.get_players_pos() );
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		Position cell_pos;
		cell_pos.x = (int)floorf(
			( (event->motion.x - map_x_offset) / 
			( (float)(MAP_COLS*TILE_SIZE) / MAP_COLS) ) );

		cell_pos.y = (int)floorf( 
			((event->motion.y - map_y_offset) / 
			((float)(MAP_ROWS*TILE_SIZE) / MAP_ROWS) ) );

		if( cell_pos.x >= 0 && cell_pos.x <= MAP_COLS-1 && 
			cell_pos.y >= 0 && cell_pos.y <= MAP_ROWS-1 && 
			map_.is_pos_walkable( cell_pos ) )
		{
			path_list_.clear();
			path_list_ = a_star.get_best_path( cell_pos, map_.getplayer_01_pos_() );
			path_list_.push_back( cell_pos );
		}
	}
}

void MapSettings::update()
{
}

void MapSettings::draw( SDL_Surface* screen )
{
	std::vector<std::vector<int>> map_data = map_.get_map();
	
	SDL_Rect src_rect_;
	src_rect_.x = src_rect_.y = 0;
	src_rect_.w = src_rect_.h = TILE_SIZE;
	
	SDL_Rect dst_rect_;
	dst_rect_.w = dst_rect_.h = TILE_SIZE;
	
	SDL_Surface* current_tex;
	
	for(int col = 0; col < MAP_COLS; ++col )
	{
		for(int row = 0; row < MAP_ROWS; ++row )
		{
			switch( map_data[col][row] )
			{
			case map_.WALKABLE:
				current_tex = green_tex_;
				break;
			case map_.WALL:
				current_tex = black_tex_;
				break;
			default:
				current_tex = white_tex_;
				break;
			}
			
			dst_rect_.x = map_x_offset + col*TILE_SIZE;
			dst_rect_.y = map_y_offset + (row*TILE_SIZE);
			SDL_BlitSurface( current_tex, &src_rect_, screen, &dst_rect_ );
		}
	}
	
	current_tex = white_tex_;
	for( std::vector<Position>::iterator it = path_list_.begin(); it != path_list_.end(); ++it )
	{
		dst_rect_.x = map_x_offset + (*it).x*TILE_SIZE;
		dst_rect_.y = map_y_offset + (*it).y*TILE_SIZE;
		SDL_BlitSurface( current_tex, &src_rect_, screen, &dst_rect_ );
	}

	dst_rect_.x = map_x_offset + map_.getplayer_01_pos_().x*TILE_SIZE;
	dst_rect_.y = 68 + map_.getplayer_01_pos_().y*TILE_SIZE;
	SDL_BlitSurface( blue_tex_, &src_rect_, screen, &dst_rect_ );

	TextHandler::render_text( 
		100, 64 + (MAP_ROWS*TILE_SIZE) + 20, font, 
		"MAP SETTINGS", 0, 200, 0, screen );
}