#include "cImageHelper.h"

SDL_Surface* cImageHelper::LoadImage( char *file ) 
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