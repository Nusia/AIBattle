#pragma once

#include <vector>

#include <irrlicht.h>
#include "iGameState.h"
#include "cGameManager.h"
#include "cPreGameState.h"
#include "cInGameState.h"

class cStateManager
{
public:
	cStateManager( cGameManager* gameManager );

	void Init( irr::IrrlichtDevice* device );
	void Update( irr::IrrlichtDevice* device );
	void Draw( irr::IrrlichtDevice* device );

private:
	iGameState* _pActiveState;
	std::vector<iGameState*> _vGameStates;
};