#include "cInGameState.h"

void cInGameState::Init( IrrlichtDevice* device )
{
	std::cout << "Initiating ingame state.\n";
	
	_bIsDone = false;
	_bIsRunning = false;
	_nTimeElapsed = 0;
	_nTimeOfStart = device->getTimer()->getTime();

	_pEventReceiver = new cEventReceiver();
	device->setEventReceiver( _pEventReceiver );
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
	{
        PrevStateOfKeyIsDown[i] = false;
	}

	_fCamZoom = 0;
	_pMessageBox = new cMessageBoxInGame( device );

	_pVideoDriver = device->getVideoDriver();
	_pSceneManager = device->getSceneManager();
	_pGUIEnv = device->getGUIEnvironment();

	_pSceneManager->addCameraSceneNode( 
		0, 
		core::vector3df( 0, 0, 100 ), 
		core::vector3df( 0, 0, 5 ) );
		
	_pCharacterPlayer01Sprite = _pVideoDriver->getTexture("../resources/character_basic_green.png");
	_pVideoDriver->makeColorKeyTexture( _pCharacterPlayer01Sprite, core::position2d<s32>(1,1) );
	
	_pCharacterPlayer02Sprite = _pVideoDriver->getTexture("../resources/character_basic_red.png");
	_pVideoDriver->makeColorKeyTexture( _pCharacterPlayer02Sprite, core::position2d<s32>(1,1) );

	_pGround = _pVideoDriver->getTexture("../resources/ground.png");
	_pWall = _pVideoDriver->getTexture("../resources/wall.png");
	
	_pFont = _pGUIEnv->getFont("../resources/fonts/test.png");
	//_pFont = _pGUIEnv->getFont("../resources/fonts/larabie08.png");

	_pVideoDriver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
	_pVideoDriver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;

	_pChar01Node = _pSceneManager->addCubeSceneNode();
	_pChar01Node->setMaterialFlag(video::EMF_LIGHTING, false);
	_pChar01Node->setPosition( core::vector3df( 0, 0, 10 ) );
	_pChar01Node->setMaterialTexture(0, _pCharacterPlayer01Sprite);

	cMap map = *(_pGameManager->GetMap());
	std::vector< std::vector< int >> typemap = map.GetMap();
	for( int c = 0; c < MAP_COLS; ++c )
		for( int r = 0; r < MAP_ROWS; ++r )
		{
			_ppNodes[c][r] = _pSceneManager->addCubeSceneNode();
			if( typemap[c][r] == map.WALL )
			{
				_ppNodes[c][r]->setPosition( core::vector3df( -c*10, -r*10, 10 ) );
				_ppNodes[c][r]->setMaterialTexture(0, _pWall);
			}
			else if( typemap[c][r] == map.WALKABLE )
			{
				_ppNodes[c][r]->setPosition( core::vector3df( -c*10, -r*10, 0 ) );
				_ppNodes[c][r]->setMaterialTexture(0, _pGround);
			}
			_ppNodes[c][r]->setMaterialFlag(video::EMF_LIGHTING, false);
		}

	MoveCamera( 
		map.GetPlayer01Pos().X * 10, 
		map.GetPlayer01Pos().Y * 10, 
		0 );

	_pMessageBox->AddMessage( "Game started (in pause mode)." );
	_pMessageBox->AddMessage( "Press SPACE to resume." );
	std::cout << "Ingame state ready.\n";
}

void cInGameState::Update( IrrlichtDevice* device )
{
	cMap map = *(_pGameManager->GetMap());

	if( _bIsRunning )
	{
		_nTimeElapsed += device->getTimer()->getTime() - _nTimeOfLastUpdate;
		_nTimeOfLastUpdate = device->getTimer()->getTime();

		_pGameManager->InGameUpdate( device );

		if( !tmp_list_.empty() )
		{
			map.SetPlayer01Pos( tmp_list_.front() );
			tmp_list_.erase( tmp_list_.begin() );
		}
	}

	double delta = 5;
	irr::core::vector3df tmpPos;
	f32 zDelta = _fCamZoom - _pEventReceiver->MouseState.MouseWheelDelta*10;

	if( _pEventReceiver->IsAnyKeyDown() || _pEventReceiver->GetMouseState().IsButtonPressed() )
	{
		for( int c = 0; c < MAP_COLS; ++c )
		{
			for( int r = 0; r < MAP_ROWS; ++r )
			{
				tmpPos = _ppNodes[c][r]->getPosition();
				
				if( _pEventReceiver->IsKeyDown( irr::KEY_KEY_W ) )
					tmpPos.Y -= delta;
				if( _pEventReceiver->IsKeyDown( irr::KEY_KEY_S ) )
					tmpPos.Y += delta;
				if( _pEventReceiver->IsKeyDown( irr::KEY_KEY_A ) )
					tmpPos.X -= delta;
				if( _pEventReceiver->IsKeyDown( irr::KEY_KEY_D ) )
					tmpPos.X += delta;
				tmpPos.Z -= zDelta;
				
				_ppNodes[c][r]->setPosition( tmpPos );
			}
		}
	}
	tmpPos = _ppNodes[0][0]->getPosition();
	tmpPos.X -= _pGameManager->GetPlayer(1)->GetPosition().X * 10;
	tmpPos.Y -= _pGameManager->GetPlayer(1)->GetPosition().Y * 10;
	if( map.GetMap()[0][0] == map.WALKABLE ) 
		tmpPos.Z += 10;
	_pChar01Node->setPosition(tmpPos);

	_fCamZoom = _pEventReceiver->MouseState.MouseWheelDelta*10;

	if( _pEventReceiver->IsKeyDown( irr::KEY_ESCAPE ) )
		_bIsDone = true;

	if( KeyJustPressed( KEY_SPACE ) )
	{
		if( _bIsRunning )
		{
			_bIsRunning = false;
			_pMessageBox->AddMessage( "Game paused." );
		}
		else
		{
			_bIsRunning = true;
			_nTimeOfLastUpdate = device->getTimer()->getTime();
			_pMessageBox->AddMessage( "Game resumed." );
		}
	}

	_pMessageBox->Update( device );

	bool* tmpArray = _pEventReceiver->GetKeyDownArray();
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
	{
		PrevStateOfKeyIsDown[i] = tmpArray[i];
	}
}

void cInGameState::Draw( IrrlichtDevice* device )
{
	//HELP
	device->getVideoDriver()->draw2DRectangle(
		video::SColor( 200, 0, 0, 0 ), 
		core::rect<s32>(5, 5, 200, 60) );

	_pFont->draw(	L"WASD: Move camera.",
                    core::rect<s32>(10,10,100,20),
					video::SColor(255,255,255,255) );
	_pFont->draw(	L"Mousescroll: Zoom.",
                    core::rect<s32>(10,25,100,35),
					video::SColor(255,255,255,255) );
	_pFont->draw(	L"ESC: Go back.",
                    core::rect<s32>(10,40,100,50),
					video::SColor(255,255,255,255) );

	//INFO
	device->getVideoDriver()->draw2DRectangle(
		video::SColor( 200, 0, 0, 0 ), 
		core::rect<s32>(
			WIN_WIDTH-250, 0, WIN_WIDTH, 30) );

	float time = _nTimeElapsed / 1000.0;
	core::stringw text(L"Elapsed time: ");
	text.append( core::stringw( time ), 5 );
	text += L" sec.";

	_pFont->draw(	
		text,
		core::rect<s32>(
			WIN_WIDTH-245, 5, WIN_WIDTH-5, 45), 
		video::SColor(255,255,255,255) );

	//MSG-BOX
	_pMessageBox->Draw( device );
}

bool cInGameState::IsDone()
{
	return _bIsDone;
}

int cInGameState::GetNextState()
{
	return PREGAME;
}

void cInGameState::MoveCamera( int deltaX, int deltaY, int deltaZ )
{
	cMap map = *(_pGameManager->GetMap());
	if( !tmp_list_.empty() )
	{
		map.SetPlayer01Pos( tmp_list_.front() );
		tmp_list_.erase( tmp_list_.begin() );
	}
	
	irr::core::vector3df tmpPos;

	for( int c = 0; c < MAP_COLS; ++c )
		for( int r = 0; r < MAP_ROWS; ++r )
		{
			tmpPos = _ppNodes[c][r]->getPosition();

			tmpPos.X += deltaX;
			tmpPos.Y += deltaY;
			tmpPos.Z += deltaZ;
				
			_ppNodes[c][r]->setPosition( tmpPos );
		}


	tmpPos = _ppNodes[0][0]->getPosition();
	tmpPos.X -= map.GetPlayer01Pos().X * 10;
	tmpPos.Y -= map.GetPlayer01Pos().Y * 10;
	if( map.GetMap()[0][0] == map.WALKABLE ) 
		tmpPos.Z += 10;
	_pChar01Node->setPosition(tmpPos);
}

bool cInGameState::KeyJustPressed( EKEY_CODE keyCode ) const
{
	return( 
		(PrevStateOfKeyIsDown[ keyCode ] == false) &&
		_pEventReceiver->IsKeyDown( keyCode ) );
}