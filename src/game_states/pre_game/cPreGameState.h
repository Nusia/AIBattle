#pragma once

#include "cMapSettings.h"
#include "cAiSettings.h"
#include "../iGameState.h"
#include "../../helpers/cTextHandler.h"
#include "../../gui/cButton.h"
#include "../../gui/cButtonHandler.h"
#include "../../helpers/cPosition.h"
#include "../../helpers/cImageHelper.h"
#include "../../event_handler/event.h"

#define COLORKEY 255, 0, 255 //Your Transparent colour

//template <class Object> class Button;

class cPreGameState : public iGameState
{
public:
	cPreGameState(){};
	void ChangeState();
	void Init();
	void HandleInput( SDL_Event* event );
	void Update();
	void Draw( SDL_Surface* screen );
	bool IsDone();
	int GetNextState();

private:
	void _changeToMapSettings() { _pActiveState = _pMapSettings; }
	void _changeToAiSettings() { _pActiveState = _pAiSettings; }

	iPreGame* _pActiveState;
	cMapSettings* _pMapSettings;
	cAISettings* _pAiSettings;
	
	bool _bIsDone;
	TTF_Font* _pFont;
	cButtonHandler _buttonHandler;	
};
