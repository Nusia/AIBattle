#include "button.h"

Button::Button( char* text, SDL_Rect destination_rectangle, SDL_Surface* image )
: _text(text), _dest_rect(destination_rectangle), _img(image)
{
}