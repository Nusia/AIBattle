#pragma once 

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

class cTextHandler
{
public:
	static TTF_Font* GetFont( 
		char* name, 
		int size );

	static void RenderText(
		int x, int y, 
		TTF_Font *font, 
		const char* text, 
		const int R, const int G, const int B, 
		SDL_Surface* screen );
};