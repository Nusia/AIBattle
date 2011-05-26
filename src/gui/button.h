#include "SDL.h"

#include "../helpers/Position.h"

class Button
{
private:
	char* _text;
	SDL_Rect _dest_rect;
	SDL_Surface* _img;

public:
	Button(){};
	Button( char* text, SDL_Rect destination_rectangle, SDL_Surface* image );
	void update( Position mouse_pos );
	void draw();
};