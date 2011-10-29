#include "cButtonHandler.h"

void cButtonHandler::Update( cPosition mouse_pos, bool mouse_clicked )  
{
	if( mouse_clicked )
		for( std::vector<cButton*>::const_iterator it = _vButtonList.begin(); it != _vButtonList.end(); ++it )
			(*it)->Update( mouse_pos, mouse_clicked );
}

void cButtonHandler::Draw( SDL_Surface* screen )
{
	for( std::vector<cButton*>::const_iterator it = _vButtonList.begin(); it != _vButtonList.end(); ++it )
		(*it)->Draw( screen );
}

void cButtonHandler::AddButton( cButton* button )
{
	_vButtonList.push_back( button );
}