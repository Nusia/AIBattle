#pragma once

#include "SDL.h"

#include "../helpers/cPosition.h"
#include "../helpers/cTextHandler.h"
#include "../event_handler/event.h"

class cButton
{
public:
	cButton(){};
	cButton( SDL_Rect destination_rectangle, SDL_Surface* image );
	void Update( cPosition mouse_pos, bool mouse_clicked );
	void Draw( SDL_Surface* screen );

	MyEvent<void> ClickEvent;

private:
	char* _pText;
	SDL_Rect _destRect;
	SDL_Surface* _pImg;
	//Object _source_object;

	void _activateClickEvent();

	bool _isPointInsideButton( cPosition point );
};
