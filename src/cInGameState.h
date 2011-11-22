#pragma once

#include <irrlicht.h>
#include "cGameManager.h"
#include "cEventReceiver.h"
#include "iGameState.h"
#include "cAStar.h"
#include "Math.h"
#include "cMessageBoxInGame.h"

using namespace irr;

class cInGameState : public iGameState
{
public:
	cInGameState( cGameManager* gameManager ) : _pGameManager(gameManager) {};
	void Init( IrrlichtDevice* device );
	void Update( IrrlichtDevice* device );
	void Draw( IrrlichtDevice* device );
	bool IsDone();
	int GetNextState();
	void ChangeState() {};

private:
	//Functions
	//---------
	void MoveCamera( int deltaX, int deltaY, int deltaZ );
	bool KeyJustPressed( EKEY_CODE keyCode ) const;

	//Variables
	//---------
	cGameManager* _pGameManager;
	cMessageBoxInGame* _pMessageBox;

	std::vector< irr::core::vector2d<irr::s32> > tmp_list_;
	scene::ISceneNode* _ppNodes[MAP_COLS][MAP_ROWS];
	scene::ISceneNode* _pChar01Node;

	f32 _fCamZoom;

	video::IVideoDriver* _pVideoDriver;
	scene::ISceneManager* _pSceneManager;
	gui::IGUIEnvironment* _pGUIEnv;
	
	video::ITexture* _pCharacterPlayer01Sprite;
	video::ITexture* _pCharacterPlayer02Sprite;
	video::ITexture* _pGround;
	video::ITexture* _pWall;
	gui::IGUIFont* _pFont;

	cEventReceiver* _pEventReceiver;

	scene::ISceneNode* n;

	bool PrevStateOfKeyIsDown[KEY_KEY_CODES_COUNT];
	bool _bIsDone;

	bool	_bIsRunning;
	u32		_nTimeOfStart;
	u32		_nTimeOfLastUpdate;
	u32		_nTimeElapsed;
};