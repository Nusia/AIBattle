#pragma once

#include <vector>

#include "cButton.h"
#include "cPosition.h"

class cButtonHandler
{
public:
	cButtonHandler(){};
	void Update( cPosition mouse_pos, bool mouse_clicked );
	void Draw( SDL_Surface* screen );
	void AddButton( cButton* button );

private:
	std::vector< cButton* > _vButtonList;
};