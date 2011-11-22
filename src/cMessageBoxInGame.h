#pragma once

#include <irrlicht.h>
#include "cSettings.h"
#include <vector>
#include <iostream>

using namespace irr;

class cMessageBoxInGame
{
public:
	cMessageBoxInGame( IrrlichtDevice* device );
	void Update( IrrlichtDevice* device );
	void Draw( IrrlichtDevice* device );

	void AddMessage( const char* text );

private:
	gui::IGUIFont* _pFont;

	const int WIDTH;
	const int HEIGHT;
	const int MAX_NR_MSG;

	int _nBasicColor;
	int _nCurrentColor;
	int _nFlashColor;

	int _nNrOfMessages;
	int _nMsgOffset;
	int _nStartHeight;
	bool _bIsScrolling;

	std::vector< core::stringw > _vMsgList;
};

