#pragma once

#include "iPreGame.h"
#include "../../helpers/cImageHelper.h"
#include "../../helpers/cTextHandler.h"

class cAISettings : public iPreGame
{
public:
	cAISettings();
	void HandleInput( SDL_Event* event );
	void Update();
	void Draw( SDL_Surface* screen );
	
private:
	TTF_Font* _pFont;
};