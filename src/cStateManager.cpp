#include "cStateManager.h"

cStateManager::cStateManager( cGameManager* gameManager )
{
	_vGameStates.push_back( new cPreGameState( gameManager ) );
	_vGameStates.push_back( new cInGameState( gameManager ) );
	_pActiveState = _vGameStates[0];
}

void cStateManager::Init( irr::IrrlichtDevice* device )
{
	_pActiveState->Init( device );
}

void cStateManager::Update( irr::IrrlichtDevice* device )
{
	_pActiveState->Update( device );
	if( _pActiveState->IsDone() )
	{
		device->getSceneManager()->clear();
		device->getGUIEnvironment()->clear();

		_pActiveState = _vGameStates[_pActiveState->GetNextState()];
		_pActiveState->Init( device );
	}
}

void cStateManager::Draw( irr::IrrlichtDevice* device )
{
	_pActiveState->Draw( device );
}