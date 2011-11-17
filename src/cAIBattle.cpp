#include "cAIBattle.h"

using namespace irr;

cAIBattle::cAIBattle( video::E_DRIVER_TYPE driverType )
{
	_pGameManager = new cGameManager();
	_pGameManager->Init();

	cEventReceiver Receiver;
	_pIrrDevice = createDevice( driverType, core::dimension2d<u32>(1024, 768) ); 

	_pVideoDriver = _pIrrDevice->getVideoDriver();
	_pSceneManager = _pIrrDevice->getSceneManager();
	_pGuiEnv = _pIrrDevice->getGUIEnvironment();

	_pIrrDevice->setWindowCaption(L"AIBattle - now in Irrlicht Engine");
	
	_pStateManager = new cStateManager( _pGameManager );
	_pStateManager->Init( _pIrrDevice );

	while( _pIrrDevice->run() && _pVideoDriver )
	{
		if( _pIrrDevice->isWindowActive() )
		{
			_pVideoDriver->beginScene(true, true, video::SColor(0, 50, 50, 50));

			_pStateManager->Update( _pIrrDevice );

			_pSceneManager->drawAll();
			_pGuiEnv->drawAll();
			_pStateManager->Draw( _pIrrDevice );

			_pVideoDriver->endScene();
		}
	}
	_pIrrDevice->drop();
}

void cAIBattle::Draw( IrrlichtDevice* device )
{
	_pStateManager->Draw( device );
}