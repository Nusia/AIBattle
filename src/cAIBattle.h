#pragma once

#include <irrlicht.h>
#include "driverChoice.h"

#include "Math.h"
#include "cGameManager.h"
#include "cStateManager.h"
#include "cMap.h"
#include "cAStar.h"

class cAIBattle
{
public:
	cAIBattle( video::E_DRIVER_TYPE driverType );
	void Update();
	void Draw( IrrlichtDevice* device );

private:
	cGameManager* _pGameManager;
	irr::IrrlichtDevice* _pIrrDevice;
	irr::video::IVideoDriver* _pVideoDriver;
	irr::scene::ISceneManager* _pSceneManager;
	irr::gui::IGUIEnvironment* _pGuiEnv;

	cStateManager* _pStateManager;
	int _nWinWidth;
	int _nWinHeight;
};