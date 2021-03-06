#include "cMessageBoxInGame.h"

cMessageBoxInGame* cMessageBoxInGame::_pInstance = NULL;

cMessageBoxInGame::cMessageBoxInGame() : 
	WIDTH(600), HEIGHT(100), MAX_NR_MSG(5), 
	_nNrOfMessages(0), _nMsgOffset(16), _nStartHeight(16), _bIsScrolling(false),
	_nBasicColor(220), _nFlashColor(150)
{
	_nCurrentColor = _nBasicColor;
}

cMessageBoxInGame* cMessageBoxInGame::GetInstance()
{
	if(!_pInstance)
		_pInstance = new cMessageBoxInGame();

	return _pInstance;
}

void cMessageBoxInGame::Update()
{
	int realHeight = _vMsgList.size() * _nMsgOffset;
	if( ++_nStartHeight > realHeight )
		_nStartHeight = realHeight;

	_nCurrentColor += 5;
	if( _nCurrentColor > _nBasicColor )
		_nCurrentColor = _nBasicColor;
}

void cMessageBoxInGame::Draw( IrrlichtDevice* device )
{
	//if(!_pFont)
		_pFont = device->getGUIEnvironment()->getFont("../resources/fonts/larabie08_w.png");

	device->getVideoDriver()->draw2DRectangle(
		video::SColor( _nCurrentColor, 0, 0, 0 ),
		core::rect<s32>(	(WIN_WIDTH/2) - (WIDTH/2), WIN_HEIGHT - HEIGHT, 
							(WIN_WIDTH/2) + (WIDTH/2), WIN_HEIGHT) );
	
	int listSize = _vMsgList.size();
	int xPosLeft = (WIN_WIDTH/2) - (WIDTH/2) + 10;
	int xPosRight = (WIN_WIDTH/2) + (WIDTH/2) - 10;

	
	for( int i=0; i < listSize; i++ )
	{
		_pFont->draw( 
			_vMsgList[i], 
			core::rect<s32>( 
				xPosLeft, 
				WIN_HEIGHT - _nStartHeight + i*_nMsgOffset, 
				xPosRight,
				WIN_HEIGHT - _nStartHeight + (i+1)*_nMsgOffset ),
			video::SColor( 255, 255, 255, 255 ) );
	}
}

void cMessageBoxInGame::AddMessage( const char* text )
{
	_nCurrentColor = _nFlashColor;
	_vMsgList.push_back( core::stringw(text) );

	unsigned int maxSize = HEIGHT / _nMsgOffset;

	if( _vMsgList.size() > maxSize )
	{
		while( _vMsgList.size() > maxSize )
		{
			_vMsgList.erase( _vMsgList.begin() );
		}
		_nStartHeight = (_vMsgList.size()-1) * _nMsgOffset;
	}
}