#pragma once

#include <vector>

#include "button.h"
#include "../helpers/position.h"

class ButtonHandler
{
public:
	ButtonHandler(){};
	void update( Position mouse_pos, bool mouse_clicked );
	void draw( SDL_Surface* screen );
	void add_button( Button* button );

private:
	std::vector< Button* > button_list_;
};