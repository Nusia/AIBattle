#include "button_handler.h"

void ButtonHandler::update( Position mouse_pos, bool mouse_clicked )
{
	if( mouse_clicked )
		for( std::vector<Button*>::const_iterator it = button_list_.begin(); it != button_list_.end(); ++it )
			(*it)->update( mouse_pos, mouse_clicked );
}

void ButtonHandler::draw( SDL_Surface* screen )
{
	for( std::vector<Button*>::const_iterator it = button_list_.begin(); it != button_list_.end(); ++it )
		(*it)->draw( screen );
}

void ButtonHandler::add_button( Button* button )
{
	button_list_.push_back( button );
}