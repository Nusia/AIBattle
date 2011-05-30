#include "text_handler.h"

TTF_Font* TextHandler::get_font( char* name, int size )
{
	if( TTF_Init() == -1 )
		std::cout << "Could not init SDL_TTF.\n";

	TTF_Font* tmp_font = TTF_OpenFont( name, size);
	if( tmp_font == NULL )
		std::cout << "Font " << name <<  " not found: " << TTF_GetError() << "\n";
	else
		std::cout << "Font " << name <<  " found.\n";

	return tmp_font;
}

void TextHandler::render_text(
		int x, int y, 
		TTF_Font *font, 
		const char* text, 
		const int R, const int G, const int B, 
		SDL_Surface* screen )
{
	SDL_Color c = { R, G, B };
	SDL_Surface* msg = TTF_RenderText_Blended( 
		font, 
		text, 
		c );

	//Holds offsets
	SDL_Rect offset;
	//Get offsets
	offset.x = x;
    offset.y = y;

	SDL_BlitSurface( msg, NULL, screen, &offset );
}
