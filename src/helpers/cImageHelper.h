#pragma once

#define COLORKEY 255, 0, 255 //Your Transparent colour

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

class cImageHelper
{
public:
	static SDL_Surface* LoadImage(char *file);
};