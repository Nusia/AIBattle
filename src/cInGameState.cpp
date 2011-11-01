#include "cInGameState.h"

cInGameState::cInGameState( cMouse* pMouse ) : 
_pMouse( pMouse ), 
_isMouseScrollCamera( false )
{
}

void cInGameState::Init()
{
	std::cout << "Initiating ingame state.\n";
	map.Init();
	
	cam_pos_ = cPosition(0, 0);
		
	_pCharacterPlayer01Sprite = cImageHelper::LoadImage("../resources/character_basic_green.png");
	_pCharacterPlayer02Sprite = cImageHelper::LoadImage("../resources/character_basic_red.png");
	_pGround = cImageHelper::LoadImage("../resources/ground.png");
	_pWall = cImageHelper::LoadImage("../resources/wall.png");
	
	std::cout << "Ingame state ready.\n";
}

void cInGameState::HandleInput( SDL_Event* event )
{
	//SDL_GetMouseState( &cX, &cY );
	if( event->type == SDL_KEYDOWN )
	{
		if( event->key.keysym.sym == SDLK_DOWN )
			cam_pos_.y += 25;
		if( event->key.keysym.sym == SDLK_UP && cam_pos_.y > 0 )
			cam_pos_.y -= 25;
		if( event->key.keysym.sym == SDLK_RIGHT )
			cam_pos_.x += 25;
		if( event->key.keysym.sym == SDLK_LEFT && cam_pos_.x > 0)
			cam_pos_.x -= 25;
	}
	
	cAStar a_star( map.GetMap(), map.GetPlayersPos() );
	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		if( event->button.button == SDL_BUTTON_LEFT )
		{
			cPosition cell_pos;
			cell_pos.x = (int)floorf(
				( (event->motion.x + cam_pos_.x) / 
				( (float)(MAP_COLS*TILE_WIDTH) / MAP_COLS) ) );

			cell_pos.y = (int)floorf( 
				((event->motion.y + cam_pos_.y) / 
				((float)(MAP_ROWS*TILE_HEIGHT) / MAP_ROWS) ) );

			if( map.IsPosWalkable( cell_pos ) )
			{
				tmp_list_.clear();
				tmp_list_ = a_star.GetBestPath( cell_pos, map.GetPlayer01Pos() );
				tmp_list_.push_back( cell_pos );
			}
		}
		if( event->button.button == SDL_BUTTON_MIDDLE )
		{
			_isMouseScrollCamera = true;
			_posMouseScrollOrigo = _pMouse->GetCurrentPos();
		}
	}
	if( event->type == SDL_MOUSEBUTTONUP )
	{
		if( event->button.button == SDL_BUTTON_MIDDLE )
			_isMouseScrollCamera = false;
	}
	map.HandleEvent( event );
}

void cInGameState::Update()
{
	if( !tmp_list_.empty() )
	{
		map.SetPlayer01Pos( tmp_list_.front() );
		tmp_list_.erase( tmp_list_.begin() );
	}
	if( _isMouseScrollCamera )
	{
		cam_pos_.x += floor( (_pMouse->GetCurrentPos().x - _posMouseScrollOrigo.x) / 10.f );
		cam_pos_.y += floor( (_pMouse->GetCurrentPos().y - _posMouseScrollOrigo.y) / 10.f );
	}
}

void cInGameState::Draw( SDL_Surface* screen )
{
	SDL_Rect srect, drect;
	srect.x = 0;
	srect.y = 0;
	srect.w = 64;
	drect.w = TILE_WIDTH;
	std::vector< std::vector< int >> map_ = map.GetMap();

	for( int col = 0; col < MAP_COLS; ++col )
	{
		for( int row = 0; row < MAP_ROWS; ++row )
		{
			srect.h = 64;
			drect.h = TILE_HEIGHT;
			drect.x = col * TILE_WIDTH - cam_pos_.x; 
			drect.y = (Sint16)(row * TILE_HEIGHT - cam_pos_.y);

			switch( map_[col][row] )
			{
			case map.WALL: 
				srect.h = 64;
				drect.h = TILE_HEIGHT;
				SDL_BlitSurface( _pWall, &srect, screen, &drect );
				break;

			case map.WALKABLE:
				drect.h = TILE_HEIGHT;
				SDL_BlitSurface( _pGround, &srect, screen, &drect );
				break;
			}

			if( map.GetPlayer01Pos().x == col && map.GetPlayer01Pos().y == row )
			{
				srect.h = 64;
				drect.h = TILE_HEIGHT;
				drect.y = (Sint16)(row * TILE_HEIGHT - cam_pos_.y);
				SDL_BlitSurface( _pCharacterPlayer01Sprite, &srect, screen, &drect );
			}
			else if( map.GetPlayersPos()[0].x == col && map.GetPlayersPos()[0].y == row )
			{
				srect.h = 64;
				drect.h = TILE_HEIGHT;
				drect.y = (Sint16)(
					(row * TILE_HEIGHT * 0.75 - cam_pos_.y) - 
					(TILE_HEIGHT * 0.5));
				SDL_BlitSurface( _pCharacterPlayer02Sprite, &srect, screen, &drect );
			}
		}
	}
}

bool cInGameState::IsDone()
{
	return false;
}

int cInGameState::GetNextState()
{
	return PREGAME;
}
