#include "cAiSettings.h"

cAISettings::cAISettings()
{
	_pFont = cTextHandler::GetFont( "resources/fonts/larabiefont_rg.ttf", 16 );
}

void cAISettings::HandleInput( SDL_Event* event )
{
}

void cAISettings::Update()
{
}

void cAISettings::Draw( SDL_Surface* screen )
{
	cTextHandler::RenderText( 
		300, 300, _pFont, 
		"AI SETTINGS", 0, 200, 0, screen );
}