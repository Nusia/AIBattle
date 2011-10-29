#include "cButton.h"

cButton::cButton( SDL_Rect destination_rectangle, SDL_Surface* image )//, Object source_object )
: _destRect(destination_rectangle), _pImg(image)
{
	//_source_object = source_object;
}

void cButton::Update( cPosition mouse_pos, bool mouse_clicked )
{
	if( mouse_clicked && 
		_isPointInsideButton( mouse_pos ) )
		_activateClickEvent();
}

void cButton::Draw( SDL_Surface* screen )
{
	SDL_Rect img_rect;
	img_rect.x = 0;
	img_rect.y = 0;
	img_rect.w = _pImg->w;
	img_rect.h = _pImg->h;

	SDL_BlitSurface( _pImg, &img_rect, screen, &_destRect);
}

void cButton::_activateClickEvent()
{
	ClickEvent.notify();
}

bool cButton::_isPointInsideButton( cPosition point )
{
	return 
		(point.x - _destRect.x) < _destRect.w &&
		(point.x - _destRect.x) > 0 &&
		(point.y - _destRect.y) < _destRect.h &&
		(point.y - _destRect.y) > 0 ;
}