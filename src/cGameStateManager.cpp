#include "cGameStateManager.h"

cGameStateManager::cGameStateManager()
{
	_vGameStates.push_back( new cPreGameState() );
	_vGameStates.push_back( new cInGameState() );
	_pActiveState = _vGameStates[0];
	_pActiveState->Init();
}

void cGameStateManager::Update()
{
	_pActiveState->Update();
	if( _pActiveState->IsDone() )
	{
		_pActiveState = _vGameStates[_pActiveState->GetNextState()];
		_pActiveState->Init();
	}
}

void cGameStateManager::Draw( SDL_Surface* screen )
{
	_pActiveState->Draw( screen );
}

void cGameStateManager::HandleInput( SDL_Event* event )
{
	_pActiveState->HandleInput( event );
}