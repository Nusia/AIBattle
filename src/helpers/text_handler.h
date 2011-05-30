#pragma once 

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

class TextHandler
{
public:
	static TTF_Font* get_font( 
		char* name, 
		int size );

	static void render_text(
		int x, int y, 
		TTF_Font *font, 
		const char* text, 
		const int R, const int G, const int B, 
		SDL_Surface* screen );
};