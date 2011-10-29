#include "cMapSettings.h"

cMapSettings::cMapSettings()
: TILE_SIZE(16)
{
	map_.Init();
	_fMapOffsetX = 1024.f/2.f - (MAP_COLS*TILE_SIZE)/2.f;
	_fMapOffsetY = 68;

	_pFont = cTextHandler::GetFont( "../resources/fonts/larabiefont_rg.ttf", 16 );
	_pWhiteTex = cImageHelper::LoadImage( "../resources/pre_game/white.bmp" );
	_pBlackTex = cImageHelper::LoadImage( "../resources/pre_game/black.bmp" );
	_pRedTex = cImageHelper::LoadImage( "../resources/pre_game/red.bmp" );
	_pGreenTex = cImageHelper::LoadImage( "../resources/pre_game/green.bmp" );
	_pBlueTex = cImageHelper::LoadImage( "../resources/pre_game/blue.bmp" );	
}

void cMapSettings::HandleInput( SDL_Event* event )
{
	cAStar a_star( map_.GetMap(), map_.GetPlayersPos() );
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		cPosition cell_pos;
		cell_pos.x = (int)floorf(
			( (event->motion.x - _fMapOffsetX) / 
			( (float)(MAP_COLS*TILE_SIZE) / MAP_COLS) ) );

		cell_pos.y = (int)floorf( 
			((event->motion.y - _fMapOffsetY) / 
			((float)(MAP_ROWS*TILE_SIZE) / MAP_ROWS) ) );

		if( cell_pos.x >= 0 && cell_pos.x <= MAP_COLS-1 && 
			cell_pos.y >= 0 && cell_pos.y <= MAP_ROWS-1 && 
			map_.IsPosWalkable( cell_pos ) )
		{
			_vPathList.clear();
			_vPathList = a_star.GetBestPath( cell_pos, map_.GetPlayer01Pos() );
			_vPathList.push_back( cell_pos );
		}
	}
}

void cMapSettings::Update()
{
}

void cMapSettings::Draw( SDL_Surface* screen )
{
	std::vector<std::vector<int>> map_data = map_.GetMap();
	
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
				current_tex = _pGreenTex;
				break;
			case map_.WALL:
				current_tex = _pBlackTex;
				break;
			default:
				current_tex = _pWhiteTex;
				break;
			}
			
			dst_rect_.x = (Sint16)(_fMapOffsetX + col * TILE_SIZE);
			dst_rect_.y = (Sint16)(_fMapOffsetY + (row*TILE_SIZE));
			SDL_BlitSurface( current_tex, &src_rect_, screen, &dst_rect_ );
		}
	}
	
	current_tex = _pWhiteTex;
	for( std::vector<cPosition>::iterator it = _vPathList.begin(); it != _vPathList.end(); ++it )
	{
		dst_rect_.x = (Sint16)(_fMapOffsetX + (*it).x*TILE_SIZE);
		dst_rect_.y = (Sint16)(_fMapOffsetY + (*it).y*TILE_SIZE);
		SDL_BlitSurface( current_tex, &src_rect_, screen, &dst_rect_ );
	}

	dst_rect_.x = (Sint16)(_fMapOffsetX + map_.GetPlayer01Pos().x*TILE_SIZE);
	dst_rect_.y = 68 + map_.GetPlayer01Pos().y*TILE_SIZE;
	SDL_BlitSurface( _pBlueTex, &src_rect_, screen, &dst_rect_ );

	cTextHandler::RenderText( 
		100, 64 + (MAP_ROWS*TILE_SIZE) + 20, _pFont, 
		"MAP SETTINGS", 0, 200, 0, screen );
}