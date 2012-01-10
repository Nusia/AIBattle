#include "cPreGameState.h"

void cPreGameState::Init( IrrlichtDevice* device )
{
	std::cout << "Initiating pregame state.\n";
	_bIsDone = false;
	_posLastCheckpoint = _pGameManager->GetPlayer(1)->GetPosition();
	topLeftCornerOfMap = position2d<s32>(30, 65);
	tileSizeOfMap = 16;
	//tileSizeOfMap = 1004/MAP_COLS;

	IVideoDriver* driver = device->getVideoDriver();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();

	env = device->getGUIEnvironment();

	_pPlayer = driver->getTexture("../resources/character_basic_green.png");
	_pWall = driver->getTexture("../resources/wall.png");
	_pGround = driver->getTexture("../resources/ground.png");
	_pFont10 = env->getFont("../resources/fonts/larabie10.png");
	_pFont08 = env->getFont("../resources/fonts/larabie08.png");
	_pFont06 = env->getFont("../resources/fonts/larabie06.png");

	_pSkin = env->getSkin();
	_pSkin->setFont( _pFont10 );
	_pSkin->setFont( env->getBuiltInFont(), gui::EGDF_TOOLTIP );

	menu = env->addMenu();
	
	menu->addItem(L"Game", -1, true, true);
	menu->addItem(L"File", -1, true, true);
	menu->addItem(L"Show", -1, true, true);
	menu->addItem(L"Help", -1, true, true);

	irr::gui::IGUIContextMenu* submenu;
	submenu = menu->getSubMenu(0);
	submenu->addItem(L"Start game", GUI_ID_START_GAME);
	submenu->addItem(L"Quit", GUI_ID_QUIT);

	submenu = menu->getSubMenu(1);
	submenu->addItem(L"Save current AIsettings", GUI_ID_SAVE_AI_SETTINGS);
	submenu->addItem(L"Load AIsettings", GUI_ID_SAVE_AI_SETTINGS);

	submenu = menu->getSubMenu(2);
	submenu->addItem(L"Show map", GUI_ID_SHOW_MAP);
	submenu->addItem(L"Show settings", GUI_ID_SHOW_SETTINGS);

	submenu = menu->getSubMenu(3);
	submenu->addItem(L"Help", GUI_ID_HELP);
	submenu->addItem(L"About", GUI_ID_ABOUT);

	rangeList.push_back(3);
	rangeList.push_back(5);
	rangeList.push_back(10);
	rangeList.push_back(15);

	alertRangeBox = env->addComboBox( 
		irr::core::rect<irr::s32>( 400, 70, 450 , 90 ), 
		0, 1 );
	alertRangeBox->addItem( L"3");
	alertRangeBox->addItem( L"5");
	alertRangeBox->addItem( L"10");
	alertRangeBox->addItem( L"15");

	alertActionBox = env->addComboBox( 
		irr::core::rect<irr::s32>( 650, 70, 800 , 90 ), 
		0, 1 );
	alertActionBox->addItem( L"Do nothing");
	alertActionBox->addItem( L"Do nothing");
	alertActionBox->addItem( L"Do nothing");

    // Store the appropriate data in a context structure.
	context.device = device;
    context.counter = 0;
	context.gameState = this;
	context.stateToShow = SHOW_MAP;

	_pEventReceiver = new cPreGameEventReceiver(context);
	device->setEventReceiver( _pEventReceiver );

	std::cout << "Pregame state ready.\n";
}

void cPreGameState::Update( IrrlichtDevice* device )
{
	if( context.stateToShow == SHOW_MAP )
	{
		if( alertRangeBox->isVisible() )
			alertRangeBox->setVisible( false );
		if( alertActionBox->isVisible() )
			alertActionBox->setVisible( false );

		cMap map = *(_pGameManager->GetMap());
		cMouseState tmpMouse = *_pEventReceiver->getMouseState();
		if( _pEventReceiver->getMouseState()->LeftButtonDown )
		{
			if( GetMapRectangle().isPointInside( tmpMouse.Position ) )
			{
				std::vector<vector2d<s32>> playerPath = _pGameManager->GetPlayer(1)->GetPath();

				int xCell = (int)floorf(
					( (tmpMouse.Position.X - GetMapRectangle().UpperLeftCorner.X) / 
					( (float)(MAP_COLS * tileSizeOfMap) / MAP_COLS ) ) );
	
				int yCell = (int)floorf(
					( (tmpMouse.Position.Y - GetMapRectangle().UpperLeftCorner.Y) / 
					( (float)(MAP_ROWS * tileSizeOfMap) / MAP_ROWS ) ) );

				if( xCell >= 0 && xCell <= MAP_COLS-1 &&
					yCell >= 0 && yCell <= MAP_ROWS-1 &&
					map.IsPosWalkable( vector2d<s32>( xCell, yCell ) ) )
				{
					vector2d<s32> cellPos(xCell, yCell);
					if( playerPath.size() < 1 || 
						!(	playerPath.back().X == cellPos.X && 
							playerPath.back().Y == cellPos.Y  ) )
					{
						cAStar aStar( map.GetMap(), map.GetPlayersPos() );

						std::vector<vector2d<s32>> tmpList = aStar.GetBestPath( cellPos, _posLastCheckpoint );
						std::copy( tmpList.begin()+1, tmpList.end(), std::back_inserter( playerPath ) );
						playerPath.push_back( cellPos );

						_pGameManager->GetPlayer(1)->SetPath( playerPath );
						_posLastCheckpoint = cellPos;
					}
				}
			}
		}
		else if( _pEventReceiver->getMouseState()->RightButtonDown )
		{
			_pGameManager->GetPlayer(1)->ClearPath();
			_posLastCheckpoint = _pGameManager->GetPlayer(1)->GetPosition();
		}
	}
	else if( context.stateToShow == SHOW_SETTINGS )
	{
		if( !alertRangeBox->isVisible() )
			alertRangeBox->setVisible( true );
		if( !alertActionBox->isVisible() )
			alertActionBox->setVisible( true );
	}
	
}

void cPreGameState::Draw( IrrlichtDevice* device )
{
	if( context.stateToShow == SHOW_MAP )
	{
		cMap map = *(_pGameManager->GetMap());
		IVideoDriver* driver = device->getVideoDriver();
		std::vector<std::vector<int>> map_data = map.GetMap();
		SColor currentColor;
	
		rect<s32> destRect;
		rect<s32> srcRect = rect<s32>(0, 0, TILE_WIDTH, TILE_HEIGHT);
		for( int col = 0; col < MAP_COLS; ++col )
		{
			for( int row = 0; row < MAP_ROWS; ++row )
			{
				destRect = rect<s32>(	
					topLeftCornerOfMap.X + col*tileSizeOfMap, 
					topLeftCornerOfMap.Y + row*tileSizeOfMap, 
					topLeftCornerOfMap.X + (col+1)*tileSizeOfMap, 
					topLeftCornerOfMap.Y + (row+1)*tileSizeOfMap );

				switch( map_data[col][row] )
				{
				case map.WALKABLE:
					driver->draw2DImage( _pGround, destRect, srcRect );
					break;
				case map.WALL:
					driver->draw2DImage( _pWall, destRect, srcRect );
					break;
				default:
					currentColor = SColor(255, 255, 255, 255);
					driver->draw2DRectangle( currentColor, destRect );
					break;
				}
			}
		}

		int tmpX, tmpY;
		vector2d<s32> currPos;
		vector2d<s32> prevPos = vector2d<s32>(
			topLeftCornerOfMap.X + _pGameManager->GetPlayer(1)->GetPosition().X*tileSizeOfMap + (float)tileSizeOfMap/2, 
			topLeftCornerOfMap.Y + _pGameManager->GetPlayer(1)->GetPosition().Y*tileSizeOfMap + (float)tileSizeOfMap/2
			);

		std::vector< vector2d<s32> > tmpPathList = _pGameManager->GetPlayer(1)->GetPath();

		for( std::vector<vector2d<s32>>::iterator it = tmpPathList.begin(); it != tmpPathList.end(); ++it )
		{
			tmpX = topLeftCornerOfMap.X + (*it).X*tileSizeOfMap + (float)tileSizeOfMap/2;
			tmpY = topLeftCornerOfMap.Y + (*it).Y*tileSizeOfMap + (float)tileSizeOfMap/2;
			currPos = vector2d<s32>(tmpX, tmpY);
			if( prevPos.X > -1 )
				draw2DLine( driver, prevPos, currPos, SColor( 255, 0, 0, 0 ), 5 );
			prevPos = currPos;
		}

		tmpX = topLeftCornerOfMap.X + _pGameManager->GetPlayer(1)->GetPosition().X * tileSizeOfMap;
		tmpY = topLeftCornerOfMap.Y + _pGameManager->GetPlayer(1)->GetPosition().Y * tileSizeOfMap;
		driver->draw2DImage( 
			_pPlayer, 
			rect<s32>( tmpX, tmpY, tmpX + tileSizeOfMap, tmpY + tileSizeOfMap ), 
			srcRect );	
	}
	else if( context.stateToShow == SHOW_SETTINGS )
	{
		_pFont10->draw(	L"If enemy is within the range of: ",
						core::rect<s32>(30,70,300,90),
						video::SColor(255,0,0,0) );
		_pFont10->draw(	L"Execute action: ",
						core::rect<s32>(475,70,600,90),
						video::SColor(255,0,0,0) );
	}

	menu->bringToFront( menu );
}

bool cPreGameState::IsDone()
{
	return _bIsDone;
}

int cPreGameState::GetNextState()
{
	return INGAME;
}

void cPreGameState::ChangeState()
{
	irr::s32 id = alertRangeBox->getSelected();	
	_pGameManager->GetPlayer(1)->GetAISettings()->SetToCloseAlertDistance( rangeList[id] );
	_bIsDone = true;
}

rect<s32> cPreGameState::GetMapRectangle() const
{
	return rect<s32>(
		topLeftCornerOfMap.X, 
		topLeftCornerOfMap.Y, 
		topLeftCornerOfMap.X + MAP_COLS*tileSizeOfMap,
		topLeftCornerOfMap.Y + MAP_ROWS*tileSizeOfMap );
}

void cPreGameState::draw2DLine( IVideoDriver* driver, vector2d<s32> startPos, vector2d<s32> endPos, SColor color, int thickness )
{
	//Building dots in a "+"-pattern at startPos and endPos and draw lines between them.
	int counter = -floorf((float)thickness * 0.5);
	for( int i = 0; i < thickness; ++i )
	{
		driver->draw2DLine( vector2d<s32>(startPos.X, startPos.Y+counter ), vector2d<s32>( endPos.X, endPos.Y+counter ), color );
		driver->draw2DLine( vector2d<s32>(startPos.X+counter, startPos.Y ), vector2d<s32>( endPos.X+counter, endPos.Y ), color );
		counter++;
	}
}