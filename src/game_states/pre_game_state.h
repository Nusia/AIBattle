#pragma once

#include "i_game_State.h"
#include "../helpers/text_handler.h"
#include "../gui/button.h"
#include "../gui/button_handler.h"
#include "../helpers/Position.h"
#include "../event_handler/event.h"

#define COLORKEY 255, 0, 255 //Your Transparent colour

//template <class Object> class Button;

class PreGameState : public IGameState
{
public:
	PreGameState(){};
	void change_state();
	void init();
	void handle_input( SDL_Event* event );
	void update();
	void draw( SDL_Surface* screen );
	bool isDone();
	int get_next_state();

private:
	bool is_done_;
	TTF_Font* font;
	ButtonHandler button_handler_;

	SDL_Surface* load_image( char *file ) 
	{
		SDL_Surface *tmp;
		tmp = IMG_Load(file);

		if (tmp == NULL) {
			std::cout << "Error: Could not open " << file << ". " << IMG_GetError() << "\n";
		} else {
			if(SDL_SetColorKey(tmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tmp->format, COLORKEY)) == -1)
				std::cout << "Warning: colorkey will not be used, reason: " << SDL_GetError() << "\n";
		}
		return tmp;
	}	
};
