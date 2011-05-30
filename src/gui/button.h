#pragma once

#include "SDL.h"

#include "../helpers/Position.h"
#include "../helpers/text_handler.h"
#include "../event_handler/event.h"

class Button
{
public:
	Button(){};
	Button( SDL_Rect destination_rectangle, SDL_Surface* image );
	void update( Position mouse_pos, bool mouse_clicked );
	void draw( SDL_Surface* screen );

	MyEvent<void> click_event;

private:
	char* text_;
	SDL_Rect dest_rect_;
	SDL_Surface* img_;
	//Object _source_object;

	void activate_click_event();

	bool point_is_inside_button( Position point );
};
